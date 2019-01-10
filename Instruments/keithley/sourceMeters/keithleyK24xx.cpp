#include "./instruments/keithley/sourceMeters/keithleyK24xx.h"

const int timeBetweenSteps = 200;

KeithleyK24XX::KeithleyK24XX(QString* _name,
                     QString* _idn,
                     QString* _reference,
                     QString* _manufacturer,
                     int      _gpibAdd);

KeithleyK24XX::KeithleyK24XX();

KeithleyK24XX::~KeithleyK24XX();

int KeithleyK24XX::createMainObjects()
{
    #if DEBUG_INSTRUMENTS==1
        qDebug()<<Q_FUNC_INFO<<". Creating Main Objets......";
    #endif

    srqEventListener = new SRQEventListener();
    cmplEventListener = new CMPLEventListener();
    ibstaMonitor = new IBSTAMonitor();
    scpiCommandFactory = new SCPICommandFactory();
    return 0;
}
int KeithleyK24XX::createDataStructures()
{
    #if DEBUG_INSTRUMENTS==1
        qDebug()<<Q_FUNC_INFO<<". Creating Data Structures.....";
    #endif
    internalDataBuffer = new InternalDataBuffer();
    triggerCountBuffer = new TriggerCountBuffer();
    return 0;
}
int KeithleyK24XX::init(int gpibAdd)
{
    #if DEBUG_INSTRUMENTS==1
        qDebug()<<Q_FUNC_INFO<<". Initializing Objects and Connecting Listeners.....";
    #endif

    setGPIBAddress(gpibAdd);
    setGpibInstrumentHandler(openConnection());

    srqEventListener->setGpibInstrumentHandler(gpibInstrumentHandler);
    cmplEventListener->setGpibInstrumentHandler(gpibInstrumentHandler);
    ibstaMonitor->setGpibInstrumentHandler(gpibInstrumentHandler);

    setInSweepVoltageOperationMode();

    connect(cmplEventListener,SIGNAL(CMPLDetectedSignal()),this,SLOT(handleCMPLSignal()), Qt::QueuedConnection);
    connect(srqEventListener,SIGNAL(SRQDetectedSignal()),this,SLOT(handleSRQSignal()), Qt::QueuedConnection);

    queueForAsynchronousReadings = new QList<double>();
    asynchronousRes = new char[6];//{0,0,0,0,0,0};

    return 0;
}

void KeithleyK24XX::handleSRQSignal()
{

    #if DEBUG_INSTRUMENTS==1
        qDebug()<<Q_FUNC_INFO<<". Handling SRQ Signal...............";
    #endif

    char res1[] = {0,0,0,0};

    res1[3] = asynchronousRes[2]; //byte1
    res1[2] = asynchronousRes[3]; //byte2
    res1[1] = asynchronousRes[4]; //byte3
    res1[0] = asynchronousRes[5]; //byte4

    double result = NumericalDataFormatConverter::singlePrecisionDataFormatToDouble(res1);

    queueForAsynchronousReadings->append(result);

    srqEventListener->exit(0);

    emit SRQSignal();
}

void KeithleyK24XX::handleCMPLSignal(){

    #if DEBUG_INSTRUMENTS==1
        qDebug()<<Q_FUNC_INFO<<". Handling CMPL Signal...............";
    #endif

    char res1[] = {0,0,0,0};

    res1[3] = asynchronousRes[2]; //byte1
    res1[2] = asynchronousRes[3]; //byte2
    res1[1] = asynchronousRes[4]; //byte3
    res1[0] = asynchronousRes[5]; //byte4

    double result = NumericalDataFormatConverter::singlePrecisionDataFormatToDouble(res1);


    queueForAsynchronousReadings->append(result);

    cmplEventListener->exit(0);

    emit CMPLSignal();
}

int KeithleyK24XX::reset()
{
    #if DEBUG_INSTRUMENTS==1
        qDebug()<<Q_FUNC_INFO<<". Reseting Instrument...............";
    #endif
    QString inst = scpiCommandFactory->reset();
    return GPIBPort2::write(gpibInstrumentHandler,inst);
}


//Registers manipulation

/**
 ** Reset all bits of the following event registers to 0:
 ** Standard Event Register
 ** Operation Event Register
 ** Measurement Event Register
 ** Questionable Event Register
 * @brief KeithleyK24XX::clearRegisters
 * @return
 */
int KeithleyK24XX::clearRegisters()
{
    #if DEBUG_INSTRUMENTS==1
        qDebug()<<Q_FUNC_INFO<<". Clearing Registers...............";
    #endif
    QString inst;
    inst = QString("*CLS");
    GPIBPort2::write(gpibInstrumentHandler,inst);
}


/**
 * @brief KeithleyK24XX::configureStandardEventStatusEnableRegister
 * @param confWord
 * @return
 */
int KeithleyK24XX::configureStandardEventStatusEnableRegister(int confWord)
{
    if (confWord>65535 || confWord<0)
    {
        #if DEBUG_INSTRUMENTS==1
            qDebug()<<Q_FUNC_INFO<<". Configuring Standard Event Status Enable Register. ERROR -> !!! Not valid configuration value¡¡¡¡";
        #endif
        return -1;
    }
    #if DEBUG_INSTRUMENTS==1
        qDebug()<<Q_FUNC_INFO<<". Configuring Standard Event Status Enable Register...............";
    #endif
    QString output = QString( ":*ESE "+QString::number(confWord));
    GPIBPort2::write(gpibInstrumentHandler, output.toLocal8Bit().data() );
    QThread::msleep(10);
    return 0;
}

/**
 * @brief KeithleyK24XX::configureServiceRequestEnableRegister
 * @param confWord
 * @return
 */
int KeithleyK24XX::configureServiceRequestEnableRegister(int confWord)
{

    if (confWord>255 || confWord<0)
    {
        #if DEBUG_INSTRUMENTS==1
            qDebug()<<Q_FUNC_INFO<<". Configuring Service Request Enable Register. ERROR -> !!! Not valid configuration value¡¡¡¡";
        #endif
        return -1;
    }
    #if DEBUG_INSTRUMENTS==1
        qDebug()<<Q_FUNC_INFO<<". Configuring Service Request Enable Register...............";
    #endif
    QString output = QString( ":*SRE "+QString::number(confWord));
    GPIBPort2::write(gpibInstrumentHandler, output.toLocal8Bit().data() );
    QThread::msleep(10);
    return 0;
}

/**
 * @brief KeithleyK24XX::sendOPCCommand
 * @return
 */
int KeithleyK24XX::sendOPCCommand()
{
    #if DEBUG_INSTRUMENTS==1
        qDebug()<<Q_FUNC_INFO<<". Sending *OPC Command...............";
    #endif
    QString output = QString( "*OPC" );
    GPIBPort2::write(gpibInstrumentHandler, output.toLocal8Bit().data() );
    return 0;
}
/**
 * @brief KeithleyK24XX::setTimeout
 * @param device
 * @param timo
 * @return
 */
int KeithleyK24XX::setTimeout(int timo)
{

    #if DEBUG==1
        qDebug()<<Q_FUNC_INFO<<". Setting the Keithley Time Out ......";
    #endif
    GPIBPort2::setInstrumentTimeout(gpibInstrumentHandler, timo);
    return 0;
}

//RANGES
double KeithleyK24XX::getMaxVoltageSourceAtVoltageRange(double _vr){return 0.0;}
double KeithleyK24XX::getMaxVoltageMeasureAtVoltageRange(double _vr){return 0.0;}
double KeithleyK24XX::getVoltageComplianceAtVoltageRange(double _vr){return 0.0;}

double KeithleyK24XX::getMaxCurrentSourceAtCurrentRange(double _cr){return 0.0;}
double KeithleyK24XX::getMaxCurrentMeasureAtCurrentRange(double _cr){return 0.0;}
double KeithleyK24XX::getCurrentComplianceAtCurrentRange(double _cr){return 0.0;}

double KeithleyK24XX::getAbsoluteMaxVoltage(){return 0.0;}
double KeithleyK24XX::getAbsoluteMaxPower(){return 0.0;}


//COMMUNICATIONS
int KeithleyK24XX::getGPIBAddress() {return gpibAddress;}
int KeithleyK24XX::setGPIBAddress(int newAddress){gpibAddress=newAddress;}
int KeithleyK24XX::getGpibInstrumentHandler() {return gpibInstrumentHandler;}
void KeithleyK24XX::setGpibInstrumentHandler(int gpibInstHandler){gpibInstrumentHandler=gpibInstHandler;}

//
int KeithleyK24XX::enableOutput()
{
    #if DEBUG_INSTRUMENTS==1
        qDebug()<<Q_FUNC_INFO<<". Enabling the output...............";
    #endif
    QString inst = scpiCommandFactory->enableOutput(true);
    return GPIBPort2::write(gpibInstrumentHandler,inst);
}

int KeithleyK24XX::disableOutput(){
    QString inst = scpiCommandFactory->enableOutput(false);
    return GPIBPort2::write(gpibInstrumentHandler,inst);
}
int KeithleyK24XX::redirectOutputToRear(){
    QString inst = scpiCommandFactory->terminalsRoute(true);
    return GPIBPort2::write(gpibInstrumentHandler,inst);
}
int KeithleyK24XX::redirectOutputToFront(){
    QString inst = scpiCommandFactory->terminalsRoute(false);
    return GPIBPort2::write(gpibInstrumentHandler,inst);
}

/**
 * @brief check the connection with the instrument sending the IDN query and waiting for an error or not.
 *
 * @param pad is an integer that represents the primary GPIB address where from the Keithley 2400.
 */


int KeithleyK24XX::checkPresence(){
    int status = EXIT_SUCCESS;

#ifndef TEST
    QString inst = scpiCommandFactory->idnQuery();
    QVariant result;

    status = GPIBPort2::write(gpibInstrumentHandler,inst);

    if (status != EXIT_SUCCESS) return status;

    status = GPIBPort2::read(gpibInstrumentHandler,READ_SIZE,result);
#endif
    return status;
}


/**
 * @brief Open conection that set up the connection with the PAD device.
 *
 * @param pad is an integer that represents the primary GPIB address where from the Keithley 2400.
 */
int KeithleyK24XX::openConnection()
{  
    return GPIBPort2::openConnection(gpibAddress,0);
}

/**
 * @brief Disable the Buffer of readings.
 * This action command is used to disable the buffer of readings.
 */

int KeithleyK24XX::disableBufferOfReadings()
{
    QString inst = scpiCommandFactory->disableBufferOfReadings();
    return GPIBPort2::write(gpibInstrumentHandler,inst);
}

/**
 * @brief Enable the Buffer of readings.
 * This action command is used to enable the buffer of readings.
 */

int KeithleyK24XX::enableBufferOfReadings()
{
    QString inst = scpiCommandFactory->enableBufferOfReadings();
    return GPIBPort2::write(gpibInstrumentHandler,inst);
}

/**
 * @brief Clear the Buffer of readings.
 * This action command is used to clear the buffer of readings. If you do
 * not clear the buffer, a subsequent store will overwrite the old read-
 * ings.
 */

int KeithleyK24XX::clearBufferOfReadings()
{
    QString inst = scpiCommandFactory->clearBufferOfReadings();
    return GPIBPort2::write(gpibInstrumentHandler,inst);
}

/**
 * @brief Clear the Trigger Count Buffer.
 * This action command is used to clear the trigger count buffer.
 * More info = http://www.keithley.com/data?asset=3814
 */

int KeithleyK24XX::clearTriggerCountBuffer()
{
    QString inst = scpiCommandFactory->clearTriggerCountBuffer();
    return GPIBPort2::write(gpibInstrumentHandler,inst);
}

/**
 * @brief Set the size of the Buffer of readings.
 * This command is used to specify the size of the buffer
 */

int KeithleyK24XX::setBufferOfReadingsSize(int _size)
{
    QString inst = scpiCommandFactory->setBufferOfReadingsSize(_size);
    return GPIBPort2::write(gpibInstrumentHandler,inst);
}

/**
  * @brief Gets the identification string of the instrument
  *
  * @param None
  * @return A QString with the identification of the instrument.
  */

QString KeithleyK24XX::getIDN()
{
    int status = 0;
    QString inst = scpiCommandFactory->idnQuery();
    GPIBPort2::write(gpibInstrumentHandler,inst);
    QVariant idn;

    status = GPIBPort2::read(gpibInstrumentHandler,READ_SIZE,idn);

    if (status!=0) return NULL; else return idn.toString().toLocal8Bit();
}

/**
 * @brief Turn off concurrent functions
 *
 */
int  KeithleyK24XX::turnOffConcurrentFunctions()
{
    QString inst = scpiCommandFactory->turnOffConcurrentFunctions();
    return GPIBPort2::write(gpibInstrumentHandler,inst);
}


/**
  * @brief SMU Output Off Mode configuration
  *
  * @param smuOffModeIndex Is an integer used to decode the type of output mode, from the comboBox
  * index(widget) in the KeithleyK24XX config UI.
  */

int KeithleyK24XX::smuOffMode(int smuOffModeIndex)
{
    QString inst;
    switch ( smuOffModeIndex ) {
    case NORMAL:
        inst = QString(":OUTP:SMOD NORM");
        break;
    case HIGH_Z:
        inst = QString(":OUTP:SMOD HIMP");
        break;
    case ZERO:
        inst = QString(":OUTP:SMOD ZERO");
        break;
    case GUARD:
        inst = QString(":OUTP:SMOD GUAR");
        break;
    default:
        inst = QString(":OUTP:SMOD NORM");
        break;
    }
    return GPIBPort2::write(gpibInstrumentHandler,inst);
}

/**
  * @brief SMU Auto Zero configuration
  *
  * @param smuAutoZeroIndex Is an integer used to decode the type of auto zero config, from
  * combo box index(widget) in the KeithleyK24XX config UI.
  */

int KeithleyK24XX::smuAutoZero(int smuAutoZeroIndex)
{
    QString inst;
    switch ( smuAutoZeroIndex ) {
    case AZERO_ALWAYS:
        inst = QString(":SYST:AZER:STAT ON");
        break;
    case AZERO_ONCE:
        inst = QString(":SYST:AZER:STAT ONCE");
        break;
    case AZERO_OFF:
        inst = QString(":SYST:AZER:STAT OFF");
        break;
    default:
        inst = QString(":SYST:AZER:STAT ON");
        break;
    }

    return GPIBPort2::write(gpibInstrumentHandler,inst);
}


//**************************************************************************************************************
//**************************************************************************************************************
//*********************************************OPERATION MODES**************************************************
//**************************************************************************************************************
//**************************************************************************************************************


int KeithleyK24XX::setInSweepVoltageOperationMode(){operationMode = SWEEP_VOLTAGE;}
int KeithleyK24XX::setInSweepCurrentOperationMode(){operationMode = SWEEP_CURRENT;}
int KeithleyK24XX::setInStepVoltageOperationMode(){operationMode = STEP_VOLTAGE;}
int KeithleyK24XX::setInStepCurrentOperationMode(){operationMode = STEP_CURRENT;}
int KeithleyK24XX::setInBiasVoltageOperationMode(){operationMode = BIAS_VOLTAGE;}
int KeithleyK24XX::setInBiasCurrentOperationMode(){operationMode = BIAS_CURRENT;}
int KeithleyK24XX::setInPulsedSweepVoltageOperationMode(){operationMode = PULSED_SWEEP_VOLTAGE;}
int KeithleyK24XX::setInPulsedSweepCurrentOperationMode(){operationMode = PULSED_SWEEP_CURRENT;}
int KeithleyK24XX::setInVoltmeterOperationMode(){operationMode = VOLTMETER;}
int KeithleyK24XX::setInAmmeterOperationMode(){operationMode = AMMETER;}

/**
  * @brief SMU Source Mode configuration
  *
  * @param sourceModeIndex Is an integer used to decode the type of source mode, from the comboBox
  * index(widget) in the KeithleyK24XX config UI.
  */

int KeithleyK24XX::configSourceMode(int sourceModeIndex)
{
    if ( voltageMeasureType( sourceModeIndex ) ) return configAsVoltageSource();
    else if ( currentMeasureType( sourceModeIndex ) ) return configAsCurrentSource();
    return 0;
}

/**
  * @author David Sánchez Sánchez
  * @brief SMU Sets the Keithley In Voltage Source Mode
  *
  * @param none
  */

int KeithleyK24XX::configAsVoltageSource()
{
    QString inst = scpiCommandFactory->setInVoltageSourceMode();
    return GPIBPort2::write(gpibInstrumentHandler,inst);
}

/**
  * @author David Sánchez Sánchez
  * @brief SMU Sets the Keithley In Current Source Mode
  *
  * @param none
  */

int KeithleyK24XX::configAsCurrentSource()
{
    QString inst = scpiCommandFactory->setInCurrentSourceMode();
    return GPIBPort2::write(gpibInstrumentHandler,inst);
}

/**
  * @author David Sánchez Sánchez
  * @brief SMU Sets the Keithley In Fixed Voltage Source Mode
  *
  * @param none
  */

int KeithleyK24XX::setFixedVoltageSourceMode()
{
    QString inst = scpiCommandFactory->setInFixedVoltageSourceMode();
    return GPIBPort2::write(gpibInstrumentHandler,inst);
}

/**
  * @author David Sánchez Sánchez
  * @brief SMU Sets the Keithley In Fixed Current Source Mode
  *
  * @param none
  */

int KeithleyK24XX::setFixedCurrentSourceMode()
{
    QString inst = scpiCommandFactory->setInFixedCurrentSourceMode();
    return GPIBPort2::write(gpibInstrumentHandler,inst);
}

/**
  * @author David Sánchez Sánchez
  * @brief SMU Sets the Keithley In Voltage Measure Mode
  *
  * @param none
  */

int KeithleyK24XX::configAsVoltageMeasure()
{
    QString inst = scpiCommandFactory->setInVoltageMeasureMode();
    return GPIBPort2::write(gpibInstrumentHandler,inst);
}

/**
  * @author David Sánchez Sánchez
  * @brief SMU Sets the Keithley In Current Measure Mode
  *
  * @param none
  */

int KeithleyK24XX::configAsCurrentMeasure()
{
    QString inst = scpiCommandFactory->setInCurrentMeasureMode();
    return GPIBPort2::write(gpibInstrumentHandler,inst);
}

/**
  * @brief Select the source Range for measuring.
  *
  * @param sourceModeIndex An int that cointains the source mode index (current or voltage).
  * @param sourceRange A double that holds source range value.
  */



//**************************************************************************************************************
//**************************************************************************************************************
//*********************************************OPERATION MODES END**********************************************
//**************************************************************************************************************
//**************************************************************************************************************


int KeithleyK24XX::sourceRange(int sourceModeIndex, double sourceRange)
{
    if ( voltageMeasureType( sourceModeIndex ) ) return setVoltageSourceRange(sourceRange);
    else if ( currentMeasureType( sourceModeIndex ) ) return setCurrentSourceRange(sourceRange);
    return 0;
}


/**
  * @author David Sánchez Sánchez
  * @brief SMU Sets the Keithley Voltage Source Range
  *
  * @param double with the range
  */

int KeithleyK24XX::setVoltageSourceRange(double _range)
{
    QString inst = scpiCommandFactory->setVoltageSourceRange(_range);
    return GPIBPort2::write(gpibInstrumentHandler,inst);
}

/**
  * @author David Sánchez Sánchez
  * @brief SMU Sets the Keithley In Current Source Range
  *
  * @param double with the range
  */

int KeithleyK24XX::setCurrentSourceRange(double _range)
{
    QString inst = scpiCommandFactory->setCurrentSourceRange(_range);
    return GPIBPort2::write(gpibInstrumentHandler,inst);
}

/**
  * @brief Data format selection.
  *
  * @param voltageSource A bool that indicates if we are in voltage or current cource.
  * @param readbackSource A bool that indicates wether or not readback source value.
  * @param readMeasure A bool that indicates wether or not read the measure result.
  * @param collectTimestamps A bool that indicates wether or not retrieves the time stamps.
  */

int KeithleyK24XX::formatElements( bool voltageSource,
                                    bool readbackSource,
                                    bool readMeasure,
                                    bool collectTimestamps)
{

    //QString output = ":FORM:ELEM VOLT, CURR, TIME";
    int i=0;
    QString inst = ":FORM:ELEM ";

    if( voltageSource)
    {
        if (readbackSource){
            inst.append("VOLT");
            i++;
        }
        if (readMeasure){
            if (i>0) inst.append(", CURR");
            else
            {
                inst.append("CURR");
                i++;
            }
        }
        if (collectTimestamps){
            if (i>0) inst.append(", TIME");
            else
            {
                inst.append("TIME");
                i++;
            }
        }
    }
    else
    {
        if (readbackSource){
            inst.append("CURR");
            i++;
        }
        if (readMeasure){
            if (i>0) inst.append(", VOLT");
            else
            {
                inst.append("VOLT");
                i++;
            }
        }
        if (collectTimestamps){
            if (i>0) inst.append(", TIME");
            else
            {
                inst.append("TIME");
                i++;
            }
        }
    }
    return GPIBPort2::write(gpibInstrumentHandler,inst);
}

/**
  * @brief Data format selection to current reading only.
  */

int KeithleyK24XX::setFormatCurrentReadingOnly()
{
    QString inst = ":FORM:ELEM CURR";
    return GPIBPort2::write(gpibInstrumentHandler,inst);
}

/**
  * @brief Data format selection to voltage reading only.
  */

int KeithleyK24XX::setFormatVoltageReadingOnly()
{
    QString inst = ":FORM:ELEM VOLT";
    return GPIBPort2::write(gpibInstrumentHandler,inst);
}

/**
  * @brief Sets the Keithley Data format as Single Precision.
  */

int KeithleyK24XX::setDataFormatAsSinglePrecision()
{
    QString inst = ":FORM:DATA SRE";
    return GPIBPort2::write(gpibInstrumentHandler,inst);
}

/**
  * @brief Sets the Keithley Data format as ASCII.
  */

int KeithleyK24XX::setDataFormatAsASCII()
{
    QString inst = ":FORM:DATA ASC";
    return GPIBPort2::write(gpibInstrumentHandler,inst);
}

/**
  * @brief Disable all measurement functions.
  */

int KeithleyK24XX::disableAllMeasurementFunctions()
{
    QString inst = ":SENS:FUNC:OFF:ALL";
    return GPIBPort2::write(gpibInstrumentHandler,inst);
}

/**
  * @brief Enable or disable 4 wires measure.
  *
  * @param status Is a bool that eneables or disables 4 wires measure
  */

int KeithleyK24XX::fourWiresMeasure(bool status)
{
    QString inst;
    if( status )
        inst = ":SYST:RSEN ON";
    else
        inst = ":SYST:RSEN OFF";

    return GPIBPort2::write(gpibInstrumentHandler,inst);
}

/**
  * @brief Measure range selection.
  *
  * @param sourceModeIndex An int that contains the source mode index from the keithley
  * ui's combobox( voltage or current ).
  * @param sourceRangeIndex And int that contains the source range index from the keithley ui's
  * combobox.
  */
int KeithleyK24XX::measureRange( int sourceModeIndex, double sourceRange )
{
    if( voltageMeasureType( sourceModeIndex ) ) return setCurrentMeasureRange(sourceRange);
    else if ( currentMeasureType( sourceModeIndex ) ) return setVoltageMeasureRange(sourceRange);
    return 0;
}

/**
  * @brief Set Voltage Measure Range.
  *
  * @param sourceRangeIndex And int that contains the voltage measure range
  */
int KeithleyK24XX::setVoltageMeasureRange(double sourceRange )
{
    if ( sourceRange == AUTO_MEASURE_RANGE_FLAG )
    {
        QString inst = scpiCommandFactory->setVoltageMeasureRangeInAuto( true );
        return GPIBPort2::write(gpibInstrumentHandler,inst);
    }
    else
    {
        QString inst = scpiCommandFactory->setVoltageMeasureRange(sourceRange);
        return GPIBPort2::write(gpibInstrumentHandler,inst);
    }

}


/**
  * @brief Set Current Measure Range.
  *
  * @param sourceRangeIndex And int that contains the current measure range
  */
int KeithleyK24XX::setCurrentMeasureRange(double sourceRange )
{
    if ( sourceRange == AUTO_MEASURE_RANGE_FLAG )
    {
        QString inst = scpiCommandFactory->setCurrentMeasureRangeInAuto( true );
        return GPIBPort2::write(gpibInstrumentHandler,inst);
    }
    else
    {
        QString inst = scpiCommandFactory->setCurrentMeasureRange(sourceRange);
        return GPIBPort2::write(gpibInstrumentHandler,inst);
    }
}

/**
  * @brief Set measure compliance.
  *
  * @param sourceModeIndex An int that contains the source mode index from the keithley
  * ui's combobox( voltage or current ).
  * @param measureCompliance A double that contains the complaince value desired.
  */

int KeithleyK24XX::measureCompliance(int sourceModeIndex, double measureCompliance)
{
    if ( voltageMeasureType( sourceModeIndex ) ) return setCurrentMeasureCompliance( measureCompliance );
    else if ( currentMeasureType( sourceModeIndex ) ) return setVoltageMeasureCompliance( measureCompliance );
    return 0;
}

/**
  * @brief Set the current measure compliance.
  *
  * @param measureCompliance A double that contains the complaince value desired.
  */

int KeithleyK24XX::setCurrentMeasureCompliance(double measureCompliance)
{
    QString inst = scpiCommandFactory->setCurrentCompliance(measureCompliance);
    return GPIBPort2::write(gpibInstrumentHandler,inst);
}

/**
  * @brief Set the voltage measure compliance.
  *
  * @param measureCompliance A double that contains the complaince value desired.
  */

int KeithleyK24XX::setVoltageMeasureCompliance(double measureCompliance)
{
    QString inst = scpiCommandFactory->setVoltageCompliance(measureCompliance);
    return GPIBPort2::write(gpibInstrumentHandler,inst);
}

/**
  * @brief set delay time (settling time)
  *
  * @param measureDelay Is a double that holds settling measure time (delay) between 0 and 999.99s.
  */

int KeithleyK24XX::setMeasureDelay( double measureDelay )
{
    QString inst = QString( ":SOUR:DEL %1" ).arg( measureDelay );
    return GPIBPort2::write(gpibInstrumentHandler,inst);
}

/**
  * @brief Enable or disable beeper (sound)
  *
  * @param status A bool that defines wether or not enable or disable the beeper.
  */

int KeithleyK24XX::beeper( bool status )
{
    QString inst;
    if( status )
        inst = ":SYST:BEEP:STAT ON";
    else
        inst = ":SYST:BEEP:STAT OFF";

    return GPIBPort2::write(gpibInstrumentHandler,inst);
}

/**
  * @brief Executes and set ups a beep tone.
  *
  * @param frequency An int that contains the beep frequency (65 to 2e6 Hz).
  * @param time A double that holds the beep duration (0 to 7.9 seconds).
  */

int KeithleyK24XX::beeperTone( double frequency, double time )
{
    QString inst = QString( ":SYST:BEEP %1,%2" ).arg( frequency ).arg( time / 1000 );
    return GPIBPort2::write(gpibInstrumentHandler,inst);
    QThread::sleep(time);
}

/**
  * @brief Sets source level.
  *
  * @param sourceModeIndex An int that contains the source mode index from the keithley
  * ui's combobox( voltage or current ).
  * @param sourceLevel A double that holds desired source level.
  */
int KeithleyK24XX::sourceLevel(int sourceModeIndex, double sourceLevel)
{
    if ( voltageMeasureType( sourceModeIndex ) ) return setVoltageSourceLevel(sourceLevel);
    else if ( currentMeasureType( sourceModeIndex ) ) return setCurrentSourceLevel(sourceLevel);
    return 0;
}

/**
  * @brief Sets voltage source level.
  *
  * @param sourceLevel A double that holds desired source level.
  */
int KeithleyK24XX::setVoltageSourceLevel(double sourceLevel)
{
    QString inst = scpiCommandFactory->setVoltageSourceLevel(sourceLevel);
    return GPIBPort2::write(gpibInstrumentHandler,inst);
}

/**
  * @brief Sets current source level.
  *
  * @param sourceLevel A double that holds desired source level.
  */
int KeithleyK24XX::setCurrentSourceLevel(double sourceLevel)
{
    QString inst = scpiCommandFactory->setCurrentSourceLevel(sourceLevel);
    return GPIBPort2::write(gpibInstrumentHandler,inst);
}

/**
  * @brief Reset timestamp to zero.
  */

int KeithleyK24XX::resetTimestamp()
{
    QString inst = scpiCommandFactory->resetTimeStamps();
    return GPIBPort2::write(gpibInstrumentHandler,inst);
}


/**
  * @brief Configures the TS of the 24XX as Absolute.
  */

int KeithleyK24XX::configTimeStampAsAbsolute()
{
    QString inst = scpiCommandFactory->configTimeStampAsAbsolute();
    return GPIBPort2::write(gpibInstrumentHandler,inst);
}

/**
  * @brief Configures the TS of the 24XX as Absolute.
  */

int KeithleyK24XX::configTimeStampAsDelta()
{
    QString inst = scpiCommandFactory->configTimeStampAsDelta();
    return GPIBPort2::write(gpibInstrumentHandler,inst);
}


/**
  * @brief Enable the desired measure functions( V, C , R).
  *
  * @param sourceModeIndex An int that contains the source mode index from the keithley
  * ui's combobox( voltage or current ).
  * @param enableSource A bool indicates whether or not to enable source measurement.
  * @param enableMeasure A bool indicates whether or not to enable measure measurement.
  * @param enableResistance A bool indicates wether or not to enable resistance measurement.
  *
  * @todo Add resistence capabilities to the rest of the program.
  * @todo Instead of using a dirty if-else method to choose, create a list with the enabled params.
  */

int KeithleyK24XX::enableMeasurementFunctions(int sourceModeIndex,
                                              bool enableSource,
                                              bool enableMeasure,
                                              bool enableResitence)
{
    if( voltageMeasureType( sourceModeIndex ) )
    {
        if      (enableSource & enableMeasure & enableResitence){QString inst = scpiCommandFactory->enableMeasureFunctionsSCPI("\"VOLT\",\"CURR\",\"RES\"");return GPIBPort2::write(gpibInstrumentHandler,inst);}
        else if (enableSource & enableMeasure)                  {QString inst = scpiCommandFactory->enableMeasureFunctionsSCPI("\"VOLT\",\"CURR\"");return GPIBPort2::write(gpibInstrumentHandler,inst);}
        else if (enableSource)                                  {QString inst = scpiCommandFactory->enableMeasureFunctionsSCPI("\"VOLT\"");return GPIBPort2::write(gpibInstrumentHandler,inst);}
        else if (enableMeasure)                                 {QString inst = scpiCommandFactory->enableMeasureFunctionsSCPI("\"CURR\"");return GPIBPort2::write(gpibInstrumentHandler,inst);}
        else if (enableResitence)                               {QString inst = scpiCommandFactory->enableMeasureFunctionsSCPI("\"RES\"");return GPIBPort2::write(gpibInstrumentHandler,inst);}
        else if (enableSource & enableResitence)                {QString inst = scpiCommandFactory->enableMeasureFunctionsSCPI("\"VOLT\",\"RES\"");return GPIBPort2::write(gpibInstrumentHandler,inst);}
        else if (enableMeasure & enableResitence)               {QString inst = scpiCommandFactory->enableMeasureFunctionsSCPI("\"CURR\",\"RES\"");return GPIBPort2::write(gpibInstrumentHandler,inst);}
        else                                                    {return -1;}
    }
    else if ( currentMeasureType( sourceModeIndex ))
    {
        if( enableSource & enableMeasure & enableResitence )    {QString inst = scpiCommandFactory->enableMeasureFunctionsSCPI("\"VOLT\",\"CURR\",\"RES\"");return GPIBPort2::write(gpibInstrumentHandler,inst);}
        else if ( enableSource & enableMeasure )                {QString inst = scpiCommandFactory->enableMeasureFunctionsSCPI("\"VOLT\",\"CURR\"");return GPIBPort2::write(gpibInstrumentHandler,inst);}
        else if ( enableSource )                                {QString inst = scpiCommandFactory->enableMeasureFunctionsSCPI("\"CURR\"");return GPIBPort2::write(gpibInstrumentHandler,inst);}
        else if ( enableMeasure )                               {QString inst = scpiCommandFactory->enableMeasureFunctionsSCPI("\"VOLT\"");return GPIBPort2::write(gpibInstrumentHandler,inst);}
        else if ( enableResitence )                             {QString inst = scpiCommandFactory->enableMeasureFunctionsSCPI("\"RES\"");return GPIBPort2::write(gpibInstrumentHandler,inst);}
        else if ( enableSource & enableResitence )              {QString inst = scpiCommandFactory->enableMeasureFunctionsSCPI("\"CURR\",\"RES\"");return GPIBPort2::write(gpibInstrumentHandler,inst);}
        else if ( enableMeasure & enableResitence)              {QString inst = scpiCommandFactory->enableMeasureFunctionsSCPI("\"VOLT\",\"RES\"");return GPIBPort2::write(gpibInstrumentHandler,inst);}
        else                                                    {return -1;}
    }
    else    {return -1;}
}


/**
  * @brief Enable or disable the pulse mode for keithley 2430.
  *
  * @param enablePulseMode Is a bool that eneables or disables the pulse mode.
  */

int KeithleyK24XX::enablePulseMode( bool enablePulseMode )
{
    QString inst;
    if( enablePulseMode )   inst = ":SOUR:FUNC:SHAP PULS";
    else                    inst = ":SOUR:FUNC:SHAP DC";

    return GPIBPort2::write(gpibInstrumentHandler,inst);
}

/**
  * @brief Sets sweep starting point
  *
  * @param sourceModeIndex An int that contains the source mode index from the keithley
  * ui's combobox( voltage or current ).
  * @param sweepStart A double holding the sweep starting point value.
  */
int KeithleyK24XX::setSweepStart( const int sourceModeIndex, const double sweepStart)
{
    QString inst;

    switch( sourceModeIndex ){
    case VOLTAGE_PULSED_SWEEP:
    case VOLTAGE_SWEEP :
        inst = scpiCommandFactory->setVoltageSweepStart(sweepStart);
        return GPIBPort2::write(gpibInstrumentHandler,inst);
        break;
    case CURRENT_PULSED_SWEEP:
    case CURRENT_SWEEP:
        inst = scpiCommandFactory->setCurrentSweepStart(sweepStart);
        return GPIBPort2::write(gpibInstrumentHandler,inst);
        break;
    default:
        //nothing todo
        return -1;
        break;
    }
}

/**
  * @brief Sets sweep lasts point
  *
  * @param sourceModeIndex An int that contains the source mode index from the keithley
  * ui's combobox( voltage or current ).
  * @param sweepStop A double holding the sweep last point.
  */
int KeithleyK24XX::setSweepStop(const int sourceModeIndex, const double sweepStop)
{
    QString inst;

    switch( sourceModeIndex ){
    case VOLTAGE_PULSED_SWEEP:
    case VOLTAGE_SWEEP :
        inst = scpiCommandFactory->setVoltageSweepStop(sweepStop);
        return GPIBPort2::write(gpibInstrumentHandler,inst);
        break;
    case CURRENT_PULSED_SWEEP:
    case CURRENT_SWEEP:
        inst = scpiCommandFactory->setCurrentSweepStop(sweepStop);
        return GPIBPort2::write(gpibInstrumentHandler,inst);
        break;
    default:
        //nothing todo
        return -1;
        break;
    }
}

/**
  * @brief Sets sweep step value
  *
  * @param sourceModeIndex An int that contains the source mode index from the keithley
  * ui's combobox( voltage or current ).
  * @param sweepStep A double holding the sweep step value.
  */
int KeithleyK24XX::setSweepStep(const int sourceModeIndex, const double sweepStep)
{
    QString inst;

    switch( sourceModeIndex ){
    case VOLTAGE_PULSED_SWEEP:
    case VOLTAGE_SWEEP :
        inst = scpiCommandFactory->setVoltageSweepStep(sweepStep);
        return GPIBPort2::write(gpibInstrumentHandler,inst);
        break;
    case CURRENT_PULSED_SWEEP:
    case CURRENT_SWEEP:
        inst = scpiCommandFactory->setCurrentSweepStep(sweepStep);
        return GPIBPort2::write(gpibInstrumentHandler,inst);
        break;
    default:
        //nothing todo
        return -1;
        break;
    }
}

/**
  * @brief Sets sweep mode
  *
  * @param sourceModeIndex An int that contains the source mode index from the keithley
  * ui's combobox( voltage or current ).
  */
int KeithleyK24XX::setSweepMode( const int sourceModeIndex )
{

    QString inst;

    switch( sourceModeIndex ){
    case VOLTAGE_PULSED_SWEEP:
    case VOLTAGE_SWEEP :
        inst = scpiCommandFactory->setVoltageSweepMode();
        return GPIBPort2::write(gpibInstrumentHandler,inst);
        break;
    case CURRENT_PULSED_SWEEP:
    case CURRENT_SWEEP:
        inst = scpiCommandFactory->setCurrentSweepMode();
        return GPIBPort2::write(gpibInstrumentHandler,inst);
        break;
    default:
        //nothing todo
        return -1;
        break;
    }
}

/**
  * @brief Method to know if a of measure is voltage type.
  *
  * @param sourceModeIndex An int that contains the source mode index from the keithley
  * ui's combobox( voltage or current ).
  *
  * @return A bool that indicates wether the measure is voltage type or not.
  */

bool KeithleyK24XX::voltageMeasureType(int sourceModeIndex)
{
    bool status;
    switch( sourceModeIndex ){
    case VOLTAGE_SWEEP:
        status = true;
        break;
    case VOLTAGE_STEP:
        status = true;
        break;
    case VOLTAGE_MEASURE:
        status = true;
        break;
    case VOLTAGE_PULSED_SWEEP:
        status = true;
        break;
    case VOLTAGE_PULSED_NO_MEAS:
        status = true;
        break;
    case CURRENT_SWEEP:
        status = false;
        break;
    case CURRENT_STEP:
        status = false;
        break;
    case CURRENT_MEASURE:
        status = false;
        break;
    case CURRENT_PULSED_SWEEP:
        status = false;
        break;
    case CURRENT_PULSED_NO_MEAS:
        status = false;
        break;
    }
    return status;
}

/**
  * @brief Method to know if a of measure is current type.
  *
  * @param sourceModeIndex An int that contains the source mode index from the keithley
  * ui's combobox( voltage or current ).
  *
  * @return A bool that indicates wether the measure is current type or not.
  */

bool KeithleyK24XX::currentMeasureType(int sourceModeIndex)
{
    bool status;
    switch( sourceModeIndex ){
    case VOLTAGE_SWEEP:
        status = false;
        break;
    case VOLTAGE_STEP:
        status = false;
        break;
    case VOLTAGE_MEASURE:
        status = false;
        break;
    case VOLTAGE_PULSED_SWEEP:
        status = false;
        break;
    case VOLTAGE_PULSED_NO_MEAS:
        status = false;
        break;
    case CURRENT_SWEEP:
        status = true;
        break;
    case CURRENT_STEP:
        status = true;
        break;
    case CURRENT_MEASURE:
        status = true;
        break;
    case CURRENT_PULSED_SWEEP:
        status = true;
        break;
    case CURRENT_PULSED_NO_MEAS:
        status = true;
        break;
    }
    return status;    
}

double KeithleyK24XX::readTimeStamp()
{
    setDataFormatAsSinglePrecision();
    QString inst = ":SYST:TIME?";
    GPIBPort2::write(gpibInstrumentHandler,inst);


    char res[] = {0,0,0,0,0,0};
    char res1[] = {0,0,0,0};

    int errors = GPIBPort2::read(gpibInstrumentHandler,res, READ_SIZE);
    //qDebug()<<Q_FUNC_INFO<<". gpib errors = "<< errors;

    res1[3] = res[2]; //byte1
    res1[2] = res[3]; //byte2
    res1[1] = res[4]; //byte3
    res1[0] = res[5]; //byte4

    double result = NumericalDataFormatConverter::singlePrecisionDataFormatToDouble(res1);
    //qDebug()<<result;
    GPIBPort2::clearInstrument(gpibInstrumentHandler);
    return result;
}

double KeithleyK24XX::readVoltage(){

    configAsVoltageMeasure();
    setFormatVoltageReadingOnly();
    setDataFormatAsSinglePrecision();

    char* res;
    char res1[] = {0,0,0,0};

    int errors = GPIBPort2::sendReadQueryAndGetResultAsCharArray(gpibInstrumentHandler,res, READ_SIZE);
    //qDebug()<<Q_FUNC_INFO<<". gpib errors = "<< errors;

    res1[3] = res[2]; //byte1
    res1[2] = res[3]; //byte2
    res1[1] = res[4]; //byte3
    res1[0] = res[5]; //byte4

    double result = NumericalDataFormatConverter::singlePrecisionDataFormatToDouble(res1);
    //qDebug()<<result;
    //qDebug()<<Q_FUNC_INFO<<". Read Bytes: "<<GPIBPort2::getNumberOfReadBytes();
    //GPIBPort2::clearDevice();
    return result;

}

int KeithleyK24XX::readVoltageAsynchronously()
{
    int attemps = 0;
    int MAX_ATTEMPS = 200;

    if (cmplEventListener->isRunning())
    {
        #if DEBUG_INSTRUMENTS==1
            qDebug()<<Q_FUNC_INFO<<". CMPL Listener is still running!!!";
            qDebug()<<Q_FUNC_INFO<<". Waiting for the end of the listener event loop!!!";
        #endif
        while (cmplEventListener->isRunning() && attemps<MAX_ATTEMPS)
        {
            QThread::msleep(10);
            attemps++;
        }
    }
    if (cmplEventListener->isRunning())
    {
        #if DEBUG_INSTRUMENTS==1
            qDebug()<<Q_FUNC_INFO<<". CMPL Listener is running!!!";
            qDebug()<<Q_FUNC_INFO<<". Read Voltage Command Rejected!!!";
        #endif
        return -1;
    }


    configAsVoltageMeasure();
    setFormatVoltageReadingOnly();
    setDataFormatAsSinglePrecision();

    clearRegisters();
    //configureStandardEventStatusEnableRegister(1);
    //configureServiceRequestEnableRegister(16);
    //sendOPCCommand();

    cmplEventListener->start();

    //srqEventListener->start();

    int errors = GPIBPort2::sendReadQueryAsCharArrayAsynchronously(gpibInstrumentHandler,asynchronousRes, READ_SIZE);


    return 0;

}


double KeithleyK24XX::readCurrent(){

    configAsCurrentMeasure();
    setFormatCurrentReadingOnly();
    setDataFormatAsSinglePrecision();

    char res[] = {0,0,0,0,0,0};
    char res1[] = {0,0,0,0};

    int errors = GPIBPort2::sendReadQueryAndGetResultAsCharArray(gpibInstrumentHandler,res, READ_SIZE);
    //qDebug()<<Q_FUNC_INFO<<". gpib errors = "<< errors;

    res1[3] = res[2]; //byte1
    res1[2] = res[3]; //byte2
    res1[1] = res[4]; //byte3
    res1[0] = res[5]; //byte4

    double result = NumericalDataFormatConverter::singlePrecisionDataFormatToDouble(res1);
    //qDebug()<<result;
    GPIBPort2::clearInstrument(gpibInstrumentHandler);
    return result;
}

double KeithleyK24XX::read(int nBytes){

    char res[] = {0,0,0,0,0,0};
    char res1[] = {0,0,0,0};

    int errors = GPIBPort2::sendReadQueryAndGetResultAsCharArray(gpibInstrumentHandler,res, nBytes);
    //qDebug()<<Q_FUNC_INFO<<". errors = "<< errors;

    res1[3] = res[2]; //byte1
    res1[2] = res[3]; //byte2
    res1[1] = res[4]; //byte3
    res1[0] = res[5]; //byte4

    double result = NumericalDataFormatConverter::singlePrecisionDataFormatToDouble(res1);
    //qDebug()<<result;
    return result;
}

double KeithleyK24XX::readMeanVoltage(int mean){

    double acumValue = 0;

    int i=0;
    bool fi = false;

    while (!fi){

        acumValue = acumValue + readVoltage();
        i++;
        fi = (i>=mean);
    }

    //qDebug() << (acumValue/(double)mean);


    return (acumValue/(double)mean);

}

double KeithleyK24XX::readMeanCurrent(int mean){

    double acumValue = 0;

    int i=0;
    bool fi = false;

    while (!fi){

        acumValue = acumValue + readCurrent();
        i++;
        fi = (i>=mean);
    }

    //qDebug() << (acumValue/(double)mean);


    return (acumValue/(double)mean);

}

int KeithleyK24XX::setNPLC(double nplc)
{
    if (nplc==0.01 || nplc==0.1 || nplc==1 || nplc==10)
    {
        QString inst = scpiCommandFactory->setNplc(QString::number(nplc));
        return GPIBPort2::write(gpibInstrumentHandler,inst);
    }else return -1;

}
int KeithleyK24XX::initTrigger()
{
    QString inst = scpiCommandFactory->initTrigger();
    return GPIBPort2::write(gpibInstrumentHandler,inst);
}
int KeithleyK24XX::setTriggerCount(int triggerCount)
{
    QString inst = scpiCommandFactory->setTriggerCount(triggerCount);
    return GPIBPort2::write(gpibInstrumentHandler,inst);
}
QString KeithleyK24XX::getElements()
{
    int status = 0;
    QString inst = ":FORM:ELEM?";
    GPIBPort2::write(gpibInstrumentHandler,inst);
    QVariant idn;

    status = GPIBPort2::read(gpibInstrumentHandler,READ_SIZE,idn);

    if (status!=0) return NULL; else return idn.toString().toLocal8Bit();
}
int KeithleyK24XX::getNumberOfElementsToRead()
{
    int nElements = 0;
    QString elements = getElements();
    if (elements == NULL) nElements = -1;
    else
    {
        QStringList l = elements.split(",");
        nElements = l.size();
    }
    return nElements;
}
QString KeithleyK24XX::getDataFormat()
{
    int status = 0;
    QString inst = ":FORM:DATA?";
    GPIBPort2::write(gpibInstrumentHandler,inst);
    QVariant idn;

    status = GPIBPort2::read(gpibInstrumentHandler,READ_SIZE,idn);

    if (status!=0) return NULL; else return idn.toString().toLocal8Bit();
}


int KeithleyK24XX::testCommand(QString comm)
{
    return GPIBPort2::testCommand(gpibInstrumentHandler,comm);
}


//Filter

int KeithleyK24XX::enableFilter(bool e)
{
    #if DEBUG_INSTRUMENTS==1
        if (e == true) qDebug()<<Q_FUNC_INFO<<". Enabling instrument filter......";
        else qDebug()<<Q_FUNC_INFO<<". Disabling instrument filter......";
    #endif
    QString inst = scpiCommandFactory->enableFilter(e);
    return GPIBPort2::write(gpibInstrumentHandler,inst);
}
int KeithleyK24XX::setFilterCount(int count)
{
    //TODO: Add max and min
    #if DEBUG_INSTRUMENTS==1
        qDebug()<<Q_FUNC_INFO<<". Configuring the number of samples for the filter......";
    #endif
    QString inst = scpiCommandFactory->setFilterCount(count);
    return GPIBPort2::write(gpibInstrumentHandler,inst);
}
int KeithleyK24XX::configureFilterType(int filterType)
{
    //TODO: ADD filter type control
    #if DEBUG_INSTRUMENTS==1
        qDebug()<<Q_FUNC_INFO<<". Configuring the filter type......";
    #endif
    QString inst = scpiCommandFactory->setFilterType(filterType);
    return GPIBPort2::write(gpibInstrumentHandler,inst);
}
