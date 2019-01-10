#ifndef K24XXCONFIGURATIONPARAMETERS_H
#define K24XXCONFIGURATIONPARAMETERS_H



/********************************************************************************************************************************/
/********************************************************************************************************************************/
/*******************************************KEITHLEY K24XX SERIRES BOUNDARIES****************************************************/
/********************************************************************************************************************************/
/********************************************************************************************************************************/
/********************************************************************************************************************************/

//**********************************************************K2400****************************************************************
//**********************************************************K2400****************************************************************
//**********************************************************K2400****************************************************************

//K2400 MAX VOLTAGE IN VOLTS
const double K2400_ABSMAXVOLTAGE = 210.0;
//K2400 MAX OUTPUT POWER IN WATTS
const double K2400_ABSMAXPOWER = 22.0;

//K2400 VOLTAGE RANGES IN VOLTS
const double K2400_200mV_RANGE =    0.200;
const double K2400_2V_RANGE =       2.0;
const double K2400_20V_RANGE =      20;
const double K2400_200V_RANGE =     200;

//K2400 CURRENT RANGES IN AMPS
const double K2400_1uA_RANGE =      0.000001;
const double K2400_10uA_RANGE =     0.000010;
const double K2400_100uA_RANGE =    0.00010;
const double K2400_1mA_RANGE =      0.0010;
const double K2400_10mA_RANGE =     0.010;
const double K2400_100mA_RANGE =    0.10;
const double K2400_1A_RANGE =       1.0;

//K2400 MAX VOLTAGE SOURCE IN VOLTS VERSUS VOLTS RANGE
const double K2400_MAXVOLTAGESOURCE_AT_200mV_RANGE =    0.210;
const double K2400_MAXVOLTAGESOURCE_AT_2V_RANGE =       2.1;
const double K2400_MAXVOLTAGESOURCE_AT_20V_RANGE =      21.0;
const double K2400_MAXVOLTAGESOURCE_AT_200V_RANGE =     210.0;
//K2400 MAX VOLTAGE MEASURE IN VOLTS VERSUS VOLTS RANGE
const double K2400_MAXVOLTAGEMEASURE_AT_200mV_RANGE =   0.211;
const double K2400_MAXVOLTAGEMEASURE_AT_2V_RANGE =      2.11;
const double K2400_MAXVOLTAGEMEASURE_AT_20V_RANGE =     21.1;
const double K2400_MAXVOLTAGEMEASURE_AT_200V_RANGE =    211.0;

//K2400 MAX CURRENT SOURCE IN AMPS VERSUS AMPS RANGE
const double K2400_MAXCURRENTSOURCE_AT_1uA_RANGE =      0.00000105;
const double K2400_MAXCURRENTSOURCE_AT_10uA_RANGE =     0.0000105;
const double K2400_MAXCURRENTSOURCE_AT_100uA_RANGE =    0.000105;
const double K2400_MAXCURRENTSOURCE_AT_1mA_RANGE =      0.00105;
const double K2400_MAXCURRENTSOURCE_AT_10mA_RANGE =     0.0105;
const double K2400_MAXCURRENTSOURCE_AT_100mA_RANGE =    0.105;
const double K2400_MAXCURRENTSOURCE_AT_1A_RANGE =       1.05;

//K2400 MAX CURRENT MEASURE IN AMPS VERSUS AMPS RANGE
const double K2400_MAXCURRENTMEASURE_AT_1uA_RANGE =      0.000001055;
const double K2400_MAXCURRENTMEASURE_AT_10uA_RANGE =     0.00001055;
const double K2400_MAXCURRENTMEASURE_AT_100uA_RANGE =    0.0001055;
const double K2400_MAXCURRENTMEASURE_AT_1mA_RANGE =      0.001055;
const double K2400_MAXCURRENTMEASURE_AT_10mA_RANGE =     0.01055;
const double K2400_MAXCURRENTMEASURE_AT_100mA_RANGE =    0.1055;
const double K2400_MAXCURRENTMEASURE_AT_1A_RANGE =       1.055;

//K2400 COMPLIANCE LIMITS IN VOLTS VERSUS VOLTS RANGE
const double K2400_COMPLIANCE_AT_200mV_RANGE =   0.210;
const double K2400_COMPLIANCE_AT_2V_RANGE =      2.10;
const double K2400_COMPLIANCE_AT_20V_RANGE =     21.0;
const double K2400_COMPLIANCE_AT_200V_RANGE =    210.0;

//K2400 COMPLIANCE LIMITS IN AMPS VERSUS AMPS RANGE
const double K2400_COMPLIANCE_AT_1uA_RANGE =      0.00000105;
const double K2400_COMPLIANCE_AT_10uA_RANGE =     0.0000105;
const double K2400_COMPLIANCE_AT_100uA_RANGE =    0.000105;
const double K2400_COMPLIANCE_AT_1mA_RANGE =      0.00105;
const double K2400_COMPLIANCE_AT_10mA_RANGE =     0.0105;
const double K2400_COMPLIANCE_AT_100mA_RANGE =    0.105;
const double K2400_COMPLIANCE_AT_1A_RANGE =       1.05;

//**********************************************************K2410****************************************************************
//**********************************************************K2410****************************************************************
//**********************************************************K2410****************************************************************

//K2410 MAX VOLTAGE IN VOLTS
const double K2410_ABSMAXVOLTAGE = 1100.0;
//K2410 MAX OUTPUT POWER IN WATTS
const double K2410_MAXOUTPUTPOWER = 22.0;

//K2410 VOLTAGE RANGES IN VOLTS
const double K2410_200mV_RANGE =    0.200;
const double K2410_2V_RANGE =       2.0;
const double K2410_20V_RANGE =      20.0;
const double K2410_1000V_RANGE =    1000.0;

//K2410 CURRENT RANGES IN AMPS
const double K2410_1uA_RANGE =      0.000001;
const double K2410_10uA_RANGE =     0.000010;
const double K2410_100uA_RANGE =    0.00010;
const double K2410_1mA_RANGE =      0.0010;
const double K2410_20mA_RANGE =     0.020;
const double K2410_100mA_RANGE =    0.10;
const double K2410_1A_RANGE =       1.0;

//K2410 MAX VOLTAGE SOURCE IN VOLTS VERSUS VOLTS RANGE
const double K2410_MAXVOLTAGESOURCE_AT_200mV_RANGE =    0.210;
const double K2410_MAXVOLTAGESOURCE_AT_2V_RANGE =       2.1;
const double K2410_MAXVOLTAGESOURCE_AT_20V_RANGE =      21.0;
const double K2410_MAXVOLTAGESOURCE_AT_1000V_RANGE =     1100.0;
//K2410 MAX VOLTAGE MEASURE IN VOLTS VERSUS VOLTS RANGE
const double K2410_MAXVOLTAGEMEASURE_AT_200mV_RANGE =   0.211;
const double K2410_MAXVOLTAGEMEASURE_AT_2V_RANGE =      2.11;
const double K2410_MAXVOLTAGEMEASURE_AT_20V_RANGE =     21.1;
const double K2410_MAXVOLTAGEMEASURE_AT_1000V_RANGE =   1100.0;

//K2410 MAX CURRENT SOURCE IN AMPS VERSUS AMPS RANGE
const double K2410_MAXCURRENTSOURCE_AT_1uA_RANGE =      0.00000105;
const double K2410_MAXCURRENTSOURCE_AT_10uA_RANGE =     0.0000105;
const double K2410_MAXCURRENTSOURCE_AT_100uA_RANGE =    0.000105;
const double K2410_MAXCURRENTSOURCE_AT_1mA_RANGE =      0.00105;
const double K2410_MAXCURRENTSOURCE_AT_20mA_RANGE =     0.0210;
const double K2410_MAXCURRENTSOURCE_AT_100mA_RANGE =    0.105;
const double K2410_MAXCURRENTSOURCE_AT_1A_RANGE =       1.05;

//K2410 MAX CURRENT MEASURE IN AMPS VERSUS AMPS RANGE
const double K2410_MAXCURRENTMEASURE_AT_1uA_RANGE =      0.000001055;
const double K2410_MAXCURRENTMEASURE_AT_10uA_RANGE =     0.00001055;
const double K2410_MAXCURRENTMEASURE_AT_100uA_RANGE =    0.0001055;
const double K2410_MAXCURRENTMEASURE_AT_1mA_RANGE =      0.001055;
const double K2410_MAXCURRENTMEASURE_AT_20mA_RANGE =     0.02110;
const double K2410_MAXCURRENTMEASURE_AT_100mA_RANGE =    0.1055;
const double K2410_MAXCURRENTMEASURE_AT_1A_RANGE =       1.055;

//K2410 COMPLIANCE LIMITS IN VOLTS VERSUS VOLTS RANGE
const double K2410_COMPLIANCE_AT_200mV_RANGE =   0.210;
const double K2410_COMPLIANCE_AT_2V_RANGE =      2.10;
const double K2410_COMPLIANCE_AT_20V_RANGE =     21.0;
const double K2410_COMPLIANCE_AT_1000V_RANGE =   1100.0;

//K2410 COMPLIANCE LIMITS IN AMPS VERSUS AMPS RANGE
const double K2410_COMPLIANCE_AT_1uA_RANGE =      0.00000105;
const double K2410_COMPLIANCE_AT_10uA_RANGE =     0.0000105;
const double K2410_COMPLIANCE_AT_100uA_RANGE =    0.000105;
const double K2410_COMPLIANCE_AT_1mA_RANGE =      0.00105;
const double K2410_COMPLIANCE_AT_20mA_RANGE =     0.0210;
const double K2410_COMPLIANCE_AT_100mA_RANGE =    0.105;
const double K2410_COMPLIANCE_AT_1A_RANGE =       1.05;

//**********************************************************K2420****************************************************************
//**********************************************************K2420****************************************************************
//**********************************************************K2420****************************************************************

//K2420 MAX VOLTAGE IN VOLTS
const double K2420_MAXVOLTAGE = 60.0;
//K2420 MAX OUTPUT POWER IN WATTS
const double K2420_MAXOUTPUTPOWER = 66.0;
//K2420 MAX CURRENT IN AMPS
const double K2420_MAXCURRENT_0to20V = 3.0;
const double K2420_MAXCURRENT_20to60V = 1.0;

//**********************************************************K2425****************************************************************
//**********************************************************K2425****************************************************************
//**********************************************************K2425****************************************************************

//K2425 MAX VOLTAGE IN VOLTS
const double K2425_MAXVOLTAGE = 100.0;
//K2425 MAX OUTPUT POWER IN WATTS
const double K2425_MAXOUTPUTPOWERAT105VOLTS = 110.0;
const double K2425_MAXOUTPUTPOWERAT21VOLTS = 66.0;
//K2425 MAX CURRENT IN AMPS
const double K2425_MAXCURRENT_0to20V = 3.0;
const double K2425_MAXCURRENT_20to60V = 1.0;
const double K2425_MAXCURRENT_60to100V = 1.0;

//**********************************************************K2430****************************************************************
//**********************************************************K2430****************************************************************
//**********************************************************K2430****************************************************************

//K2430 MAX VOLTAGE IN VOLTS
const double K2430_MAXVOLTAGE = 100.0;
//K2430 MAX OUTPUT POWER IN WATTS
const double K2430_MAXOUTPUTPOWERAT105VOLTS = 110.0;
const double K2430_MAXOUTPUTPOWERAT21VOLTS = 66.0;
//K2430 MAX CURRENT IN AMPS
const double K2430_MAXCURRENT_0to20V = 3.0;
const double K2430_MAXCURRENT_20to60V = 1.0;
const double K2430_MAXCURRENT_60to100V = 1.0;

//**********************************************************K2440****************************************************************
//**********************************************************K2440****************************************************************
//**********************************************************K2440****************************************************************

//K2440 MAX VOLTAGE IN VOLTS
const double K2440_MAXVOLTAGE = 40.0;
//K2440 MAX OUTPUT POWER IN WATTS
const double K2440_MAXOUTPUTPOWER = 50.0;
//K2440 MAX CURRENT IN AMPS
const double K2440_MAXCURRENT_0to10V = 5.0;
const double K2440_MAXCURRENT_10to40V = 0.2;

/********************************************************************************************************************************/
/********************************************************************************************************************************/
/*******************************************KEITHLEY K24XX SERIRES BOUNDARIES ENDS***********************************************/
/********************************************************************************************************************************/
/********************************************************************************************************************************/
/********************************************************************************************************************************/



/********************************************************************************************************************************/
/********************************************************************************************************************************/
/*******************************************KEITHLEY K24XX DEFINES***************************************************************/
/********************************************************************************************************************************/
/********************************************************************************************************************************/
/********************************************************************************************************************************/



const int ASCII_DATA_FORMAT_BYTES_PER_ELEMENT = 14;

const int SINGLEPRECISION_DATA_FORMAT_BYTES_PER_ELEMENT = 4;
const int SINGLEPRECISION_DATA_FORMAT_BYTES_OF_TERMINATOR = 1;
const int SINGLEPRECISION_DATA_FORMAT_BYTES_OF_HEADER = 2;

const int NUMBER_OF_DATA_ELEMENTS_MAX = 5;

const int NUMBER_OF_POINTS_PER_SWEEP_MAX = 2499;
const int NUMBER_OF_POINTS_PER_SWEEP_MIN = 2;
const int NUMBER_OF_POINTS_PER_SWEEP_DEFAULT = 101;

const int READBUFFER_SIZE_DEFAULT = NUMBER_OF_POINTS_PER_SWEEP_DEFAULT*NUMBER_OF_DATA_ELEMENTS_MAX*SINGLEPRECISION_DATA_FORMAT_BYTES_PER_ELEMENT
        + SINGLEPRECISION_DATA_FORMAT_BYTES_OF_HEADER + SINGLEPRECISION_DATA_FORMAT_BYTES_OF_TERMINATOR;

const int READBUFFER_SIZE_MAX = NUMBER_OF_POINTS_PER_SWEEP_MAX*NUMBER_OF_DATA_ELEMENTS_MAX*SINGLEPRECISION_DATA_FORMAT_BYTES_PER_ELEMENT
                                + SINGLEPRECISION_DATA_FORMAT_BYTES_OF_HEADER + SINGLEPRECISION_DATA_FORMAT_BYTES_OF_TERMINATOR;

const int READBUFFER_SIZE_MIN = NUMBER_OF_POINTS_PER_SWEEP_MIN*NUMBER_OF_DATA_ELEMENTS_MAX*SINGLEPRECISION_DATA_FORMAT_BYTES_PER_ELEMENT
        + SINGLEPRECISION_DATA_FORMAT_BYTES_OF_HEADER + SINGLEPRECISION_DATA_FORMAT_BYTES_OF_TERMINATOR;


const double NPLC_MIN = 0.01;
const double NPLC_MAX = 10;
const double NPLC_DEFAULT = 1;

const double NPLC_FOR2430_MIN = 0.01;
const double NPLC_FOR2430_MAX = 0.1;
const double NPLC_FOR2430_DEFAULT = 0.1;


#define ENABLE   "ENABLE"
#define MEASURE_TYPE   "MEASURE_TYPE"

#define LEVEL   "LEVEL"
#define START   "START"
#define STOP    "STOP"
#define NUMBER_OF_POINTS  "NUMBER_OF_POINTS"
#define SWEEP_TYPE  "SWEEP_TYPE"
#define COMPLIANCE    "COMPLIANCE"
#define DELAY   "DELAY"

#define READBACK    "READBACK"
#define MEASURE   "MEASURE"
#define TIMESTAMPS  "TIMESTAMPS"
#define MEAS_RANGE    "MEAS_RANGE"
#define NPLC    "NPLC"
#define FILTER_TYPE "FILTER_TYPE"
#define FILTER_COUNT  "FILTER_COUNT"

#define FOUR_WIRES "4_WIRES"
#define REAR_TERMINALS "REAR_TERMINALS"
#define AUTO_ZERO   "AUTO_ZERO"
#define OFF_MODE    "OFF_MODE"

#define WIDTH   "WIDTH"
#define SOFT_OR_HARD  "SOFT_OR_HARD"
#define SOFTWARE    0
#define HARDWARE    1

#define DUT_NAME    "DUT_NAME"
#define TERMINALS_NUMBER    "TERMINALS_NUMBER"

#define T1_NAME "T1_NAME"
#define T1_DEVICE "T1_DEVICE"
#define T1_DEVICE_NAME "T1_DEVICE_NAME"
#define T2_NAME "T2_NAME"
#define T2_DEVICE "T2_DEVICE"
#define T2_DEVICE_NAME "T2_DEVICE_NAME"
#define T3_NAME "T3_NAME"
#define T3_DEVICE "T3_DEVICE"
#define T3_DEVICE_NAME "T3_DEVICE_NAME"
#define T4_NAME "T4_NAME"
#define T4_DEVICE "T4_DEVICE"
#define T4_DEVICE_NAME "T4_DEVICE_NAME"

/**
  * Combo box indexes for keithley 24xx UI, selecting the number of terminal devices
  */
#define FOUR_TERMINALS_INDEX    2
#define THREE_TERMINALS_INDEX    1
#define TWO_TERMINALS_INDEX    0


/**
  * Measurement Range combo box index definitions for keithley 24xx UI
  */

#define INDEX_MR_AUTO   0
#define INDEX_MR_1A     1
#define INDEX_MR_100MA  2
#define INDEX_MR_20MA   3
#define INDEX_MR_10MA   3
#define INDEX_MR_1MA    4
#define INDEX_MR_100UA  5
#define INDEX_MR_10UA   6
#define INDEX_MR_1UA    7

#define INDEX_MR_AUTO_2430   0
#define INDEX_MR_3A_2430     1
#define INDEX_MR_1A_2430     2
#define INDEX_MR_100MA_2430  3
#define INDEX_MR_10MA_2430   4
#define INDEX_MR_1MA_2430    5
#define INDEX_MR_100UA_2430  6
#define INDEX_MR_10UA_2430   7

#define INDEX_MR_10A_2430_PULSED    0
#define INDEX_MR_1A_2430_PULSED     1
#define INDEX_MR_100MA_2430_PULSED  2
#define INDEX_MR_10MA_2430_PULSED   3
#define INDEX_MR_1MA_2430_PULSED    4
#define INDEX_MR_100UA_2430_PULSED  5
#define INDEX_MR_10UA_2430_PULSED   6

#define INDEX_MR_1000V  1
#define INDEX_MR_200V   1
#define INDEX_MR_20V    2
#define INDEX_MR_2V     3
#define INDEX_MR_200MV  4

#define INDEX_MR_60V_2430   1

#define INDEX_MR_100V_2430   1
#define INDEX_MR_20V_2430    2
#define INDEX_MR_2V_2430     3
#define INDEX_MR_200MV_2430  4

#define INDEX_MR_100V_2430_PULSED   0
#define INDEX_MR_20V_2430_PULSED    1
#define INDEX_MR_2V_2430_PULSED     2
#define INDEX_MR_200MV_2430_PULSED  3

/**
  * Stacked widget indexes definition for keithley 24xx configuration UI
  */

#define DEVICE_INDEX    0
#define CONFIG_INDEX    1

/**
  * @brief Definition of MEASURE_TYPE (configParams) for stacked widget indexes in keithley 24xx configuration UI
  */

#define SWEEP_VOLTAGE   0
#define STEP_VOLTAGE    1
#define BIAS_VOLTAGE    2
#define SWEEP_CURRENT   3
#define STEP_CURRENT    4
#define BIAS_CURRENT    5
#define PULSED_SWEEP_VOLTAGE    6
#define PULSED_SWEEP_CURRENT    7
#define VOLTMETER 8
#define AMMETER 9

#define TEST_MODE 10

/**
  *  @brief Output states definitions for keithley device cconfigurations i.e: beeper configuration see (sweep.cpp)
  */

#define ON  "ON"
#define OFF "OFF"

/**
  *  @brief Qmaps names for keithleys 24xx configuration QMap container "configParams" (i.e: ui/bus1/keithleyconfig.cpp)
  */

#define KEITHLEY_DUT_NAME    "KeithleyDUT"
#define KEITHLEY_2400_NAME    "Keithley2400"
#define KEITHLEY_2410_NAME    "Keithley2410"
#define KEITHLEY_2420_NAME    "Keithley2420"
#define KEITHLEY_2430_NAME    "Keithley2430"

/**
  *  @brief Keithley returned data i.e. "+9.979305E-01," 13 characters for the number and 1 for the comma. This is used to chop
  *  the data for saving and printing (xml/results/k24xxdatastream.cpp)
  */

#define KEITHLEY_ONE_VALUE_STRING_SIZE    13
#define COMA_STRING_SIZE    1

/**
  * Definitions for keithley id indexes of keithley admin ui config ()
  */

#ifndef KEITHLEY_INDEX
#define KEITHLEY_INDEX

#define KEITHLEY_2400    0
#define KEITHLEY_2410    1
#define KEITHLEY_2420    2
#define KEITHLEY_2430    3
#define GND_DEVICE  4
#endif

/**
  * @brief Measure range index definitions
  */

#define AUTO_MEASURE_RANGE_FLAG 8888

/**
  * @brief SMU output off modes index definitions
  */

#define NORMAL  0
#define HIGH_Z  1
#define ZERO  2
#define GUARD  3

/**
  * @brief SMU auto zero modes index definitions
  */

#define AZERO_ALWAYS  0
#define AZERO_ONCE  1
#define AZERO_OFF  2

/**
  * @brief SMU source modes index definitions,
  */

#define VOLTAGE_SWEEP   0
#define VOLTAGE_STEP    1
#define VOLTAGE_MEASURE 2
#define CURRENT_SWEEP   3
#define CURRENT_STEP    4
#define CURRENT_MEASURE 5
#define VOLTAGE_PULSED_SWEEP    6
#define CURRENT_PULSED_SWEEP    7
#define VOLTAGE_PULSED_NO_MEAS    8
#define CURRENT_PULSED_NO_MEAS    9

/**
  * @brief Filter types indexes
  *
  * @todo Clean "chapucilla" using SCPI indexes to match keithley UI's combobox indexes,
  * might be a good idea to totally isolted it, or at least keep that in mind
  */

#define EXPONENTIAL_FILTER  3
#define MOVING_FILTER       2
#define NORMAL_FILTER       0
#define REPEAT_FILTER       1

/**
  * @brief Windows definitions for text display
  */

#define TOP_WINDOW  0
#define BOTTOM_WINDOW   1

/**
  * @brief Sweep mode definitions
  */

#define LINEAR  0
#define LOG   1

/**
  * @brief Format Status register index definitions
  */

#define ASCii  0
#define HEXadecimal   1
#define OCTal  2
#define BINary   3

/********************************************************************************************************************************/
/********************************************************************************************************************************/
/*******************************************KEITHLEY K24XX DEFINES END***********************************************************/
/********************************************************************************************************************************/
/********************************************************************************************************************************/
/********************************************************************************************************************************/


#endif // K24XXCONFIGURATIONPARAMETERS_H
