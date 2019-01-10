#ifndef KEITHLEYK24XX_H
#define KEITHLEYK24XX_H

#include "./Instruments/instrument.h"
#include "./Instruments/keithley/sourceMeters/K24xxConfigurationParameters.h"
#include "./Instruments/keithley/tools/keithleyTools.h"
#include "./Instruments/commonTools/SRQEventListener.h"
#include "./Instruments/commonTools/CMPLEventListener.h"
#include "./Instruments/commonTools/IBSTAMonitor.h"

#include "../Communications/parallelCommunications/gpib/gpibPort2.h"
#include "../GPIB/SCPICommandFactory.h"
#include "../Maths/converters/numericalDataFormatConverter.h"
#include "../Tools/bufferTools.h"

class KeithleyK24XX: public Instrument{
    Q_OBJECT
public:
    KeithleyK24XX(     QString* _name,
                       QString* _idn,
                       QString* _reference,
                       QString* _manufacturer,
                       int _gpibAdd):Instrument(_name,_idn,_reference,_manufacturer)
    {
        createMainObjects();
        createDataStructures();
        init(_gpibAdd);
    }
    KeithleyK24XX():Instrument()
    {
        createMainObjects();
        createDataStructures();
        init(DEFAULT_GPIBADDERSS_FOR_INSTRUMENTS);
    }
    ~KeithleyK24XX(){}

    int createMainObjects();
    int createDataStructures();
    int init(int gpibAdd);

    int reset();

    int sendOPCCommand();

    //Registers manipulation

    int configureStandardEventStatusEnableRegister(int confWord); // 0 -> 65535
    int configureServiceRequestEnableRegister(int confWord); // 0 -> 255
    int clearRegisters();


    virtual double getMaxVoltageSourceAtVoltageRange(double _vr);
    virtual double getMaxVoltageMeasureAtVoltageRange(double _vr);
    virtual double getVoltageComplianceAtVoltageRange(double _vr);

    virtual double getMaxCurrentSourceAtCurrentRange(double _cr);
    virtual double getMaxCurrentMeasureAtCurrentRange(double _cr);
    virtual double getCurrentComplianceAtCurrentRange(double _cr);

    virtual double getAbsoluteMaxVoltage();
    virtual double getAbsoluteMaxPower();

    int getOperationMode(){return operationMode;}
    void setOperationMode(int _om){operationMode = _om;}

    int openConnection();
    int checkPresence();

    int enableOutput();
    int disableOutput();
    int redirectOutputToFront();
    int redirectOutputToRear();

    int setNPLC(double nplc);
    int initTrigger();
    int setTriggerCount(int triggerCount);


    QString getIDN();
    int clearBufferOfReadings();
    int clearTriggerCountBuffer();
    int setBufferOfReadingsSize(int _size);
    int enableBufferOfReadings();
    int disableBufferOfReadings();

    int turnOffConcurrentFunctions();

    int smuOffMode( int smuOffModeIndex );
    int smuAutoZero( int smuAutoZeroIndex );


    //Operation modes
    int configSourceMode( int sourceModeIndex );
    int configAsVoltageSource();
    int configAsCurrentSource();
    int setFixedVoltageSourceMode();
    int setFixedCurrentSourceMode();
    int configAsVoltageMeasure();
    int configAsCurrentMeasure();

    int setInSweepVoltageOperationMode();
    int setInSweepCurrentOperationMode();
    int setInStepVoltageOperationMode();
    int setInStepCurrentOperationMode();
    int setInBiasVoltageOperationMode();
    int setInBiasCurrentOperationMode();
    int setInPulsedSweepVoltageOperationMode();
    int setInPulsedSweepCurrentOperationMode();
    int setInVoltmeterOperationMode();
    int setInAmmeterOperationMode();


    //Operation ranges
    int sourceRange(int sourceModeIndex, double sourceRange);
    int setVoltageSourceRange(double _range);
    int setCurrentSourceRange(double _range);

    int formatElements( bool voltageSource,
                         bool readbackSource,
                         bool readMeasure,
                         bool collectTimestamps );

    int setFormatCurrentReadingOnly();
    int setFormatVoltageReadingOnly();
    int setDataFormatAsSinglePrecision();
    int setDataFormatAsASCII();

    int disableAllMeasurementFunctions();
    int fourWiresMeasure( bool status );

    int measureRange( int sourceModeIndex, double sourceRange );
    int setVoltageMeasureRange(double sourceRange );
    int setCurrentMeasureRange(double sourceRange );

    int measureCompliance( int sourceModeIndex, double measureCompliance );
    int setCurrentMeasureCompliance(double measureCompliance);
    int setVoltageMeasureCompliance(double measureCompliance);

    int setMeasureDelay( double setMeasureDelay );

    int beeper( bool status );
    int beeperTone( double frequency, double time );

    int sourceLevel( int sourceModeIndex, double sourceLevel);
    int setVoltageSourceLevel(double sourceLevel);
    int setCurrentSourceLevel(double sourceLevel);


    int resetTimestamp();
    int configTimeStampAsAbsolute();
    int configTimeStampAsDelta();

    int enableMeasurementFunctions( int sourceModeIndex,
                                     bool enableVoltage = false,
                                     bool enableCurrent = false,
                                     bool enableResitence = false );

    int enablePulseMode( bool enablePulseMode );

    int setSweepStart( const int sourceModeIndex, const double sweepStart );
    int setSweepStop( const int sourceModeIndex, const double sweepStop );
    int setSweepStep( const int sourceModeIndex, const double sweepStep );
    int setSweepMode( const int sourceModeIndex );

    double  readVoltage();
    int     readVoltageAsynchronously();

    double readCurrent();
    double readMeanVoltage(int mean);
    double readMeanCurrent(int mean);
    double readTimeStamp();
    double read(int nbytes);

    //Filter

    int enableFilter(bool e);
    int setFilterCount(int count);
    int configureFilterType(int filterType);

    //Communications
    int     getGPIBAddress();
    int     setGPIBAddress(int newAddress);
    int     getGpibInstrumentHandler();
    void    setGpibInstrumentHandler(int gpibInstHandler);
    int     setTimeout(int timo);

    //Others
    int testCommand(QString comm);
    QString getElements();
    int getNumberOfElementsToRead();
    QString getDataFormat();


    void print()
    {

        Instrument::print();

        std::cout<<"*******************************************"<<std::endl;
        std::cout<<"************KEITHLEY 2400 DATA*************"<<std::endl;
        std::cout<<"*******************************************"<<std::endl;

    }

private:

    bool voltageMeasureType( int sourceModeIndex );
    bool currentMeasureType( int sourceModeIndex );

    //Operation modes
    //0 --> Sweep Voltage
    //1 --> Sweep Current
    //
    int operationMode;
    double MAX_VOLTAGE;
    double MAX_POWER;

    //Buffers
    TriggerCountBuffer* triggerCountBuffer;
    InternalDataBuffer* internalDataBuffer;

    //Communications
    int gpibInstrumentHandler;
    int gpibAddress;

public:
    //FOR ASYNCHRONOUS READINGS
    //Buffer
    QList<double> *queueForAsynchronousReadings;
    //Result
    char *asynchronousRes;


public:

    SCPICommandFactory* scpiCommandFactory;

    //Asynchronous operations
    SRQEventListener* srqEventListener;
    CMPLEventListener* cmplEventListener;

    //Registers monitors
    IBSTAMonitor* ibstaMonitor;


signals:
    void SRQSignal();
    void CMPLSignal();
private slots:
    void handleCMPLSignal();
    void handleSRQSignal();


};


#endif // KEITHLEYK24XX_H
