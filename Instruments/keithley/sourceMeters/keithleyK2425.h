#ifndef KEITHLEYK2425_H
#define KEITHLEYK2425_H

#include "./instruments/keithley/sourceMeters/keithleyK24xx.h"

class KeithleyK2425: public KeithleyK24XX{
    Q_OBJECT
public:
    KeithleyK2425(     QString* _name,
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
    KeithleyK2425():KeithleyK24XX()
    {
    }
    ~KeithleyK2425(){}

    void print();
    QDomElement toQDomElement();


private:


protected:


};

#endif // KEITHLEYK2425_H
