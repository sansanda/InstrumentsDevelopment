#ifndef KEITHLEYK2410_H
#define KEITHLEYK2410_H

#include "./instruments/keithley/sourceMeters/keithleyK24xx.h"

class KeithleyK2410: public KeithleyK24XX{
    Q_OBJECT
public:
    KeithleyK2410(     QString* _name,
                       QString* _idn,
                       QString* _reference,
                       QString* _manufacturer,
                       int      _gpibAdd):KeithleyK24XX(      _name,
                                                               _idn,
                                                               _reference,
                                                               _manufacturer,
                                                               _gpibAdd)
    {
    }
    KeithleyK2410():KeithleyK24XX()
    {
    }
    ~KeithleyK2410(){}

    double getAbsoluteMaxVoltage();

    void print();
    QDomElement toQDomElement();


private:


protected:


};

#endif // KEITHLEYK2410_H
