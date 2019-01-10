#ifndef KEITHLEYK2420_H
#define KEITHLEYK2420_H

#include "./instruments/keithley/sourceMeters/keithleyK24xx.h"

class KeithleyK2420: public KeithleyK24XX{
    Q_OBJECT
public:
    KeithleyK2420(     QString* _name,
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
    KeithleyK2420():KeithleyK24XX() {}
    ~KeithleyK2420(){}

    void print();
    QDomElement toQDomElement();


private:


protected:


};

#endif // KEITHLEYK2420_H
