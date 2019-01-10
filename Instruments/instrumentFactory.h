#ifndef INSTRUMENTFACTORY_H
#define INSTRUMENTFACTORY_H

#include "./instruments/instrument.h"
#include "./instruments/keithley/sourceMeters/keithleyK2400.h"
#include "./instruments/keithley//sourceMeters/keithleyK2410.h"
#include "./instruments/keithley//sourceMeters/keithleyK2420.h"
#include "./instruments/keithley//sourceMeters/keithleyK2425.h"
#include "./instruments/keithley//sourceMeters/keithleyK2430.h"
#include "./instruments/quadTech/LCRMeters/Q7600.h"


//Keithley
const uint K2400 =   0;
const uint K2410 =   1;
const uint K2420 =   2;
const uint K2425 =   3;
const uint K2430 =   4;

//Quadtech
const uint QUADTECH7600  =   20;

//Other instruments



//Class declaration

class InstrumentFactory {

public:

    InstrumentFactory();
    ~InstrumentFactory(); // Destructor
    static Instrument* createInstrument(int);

protected:

private:

};

#endif // INSTRUMENTFACTORY_H
