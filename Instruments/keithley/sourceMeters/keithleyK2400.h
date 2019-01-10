#ifndef KEITHLEYK2400_H
#define KEITHLEYK2400_H

#include "./instruments/keithley/sourceMeters/keithleyK24xx.h"

class KeithleyK2400: public KeithleyK24XX{
    Q_OBJECT
public:
    KeithleyK2400(     QString* _name,
                       QString* _idn,
                       QString* _reference,
                       QString* _manufacturer,
                       int      _gpibAdd):KeithleyK24XX(      _name,
                                                               _idn,
                                                               _reference,
                                                               _manufacturer,
                                                               _gpibAdd) {}
    KeithleyK2400():KeithleyK24XX(){}
    ~KeithleyK2400(){}

    double getMaxVoltageSourceAtVoltageRange(double _vr);
    double getMaxVoltageMeasureAtVoltageRange(double _vr);
    double getVoltageComplianceAtVoltageRange(double _vr);

    double getMaxCurrentSourceAtCurrentRange(double _cr);
    double getMaxCurrentMeasureAtCurrentRange(double _cr);
    double getCurrentComplianceAtCurrentRange(double _cr);

    double getAbsoluteMaxVoltage();
    double getAbsoluteMaxPower();

    void print();
    QDomElement toQDomElement();


private:


protected:


};

#endif // KEITHLEYK2400_H
