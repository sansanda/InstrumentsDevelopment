#ifndef KEITHLEYK2440_H
#define KEITHLEYK2440_H

#include "./instruments/keithley/sourceMeters/keithleyK24xx.h"

class KeithleyK2440: public KeithleyK24XX{
    Q_OBJECT
public:
    KeithleyK2440(     QString* _name,
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
    KeithleyK2440():KeithleyK24XX()
    {
    }
    ~KeithleyK2440(){}

    void print();
    QDomElement toQDomElement();


private:


protected:


};

#endif // KEITHLEYK2440_H
