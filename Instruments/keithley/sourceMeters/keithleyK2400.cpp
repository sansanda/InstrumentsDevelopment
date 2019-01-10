#include "./instruments/keithley/sourceMeters/keithleyK2400.h"


KeithleyK2400::KeithleyK2400(QString* _name,
              QString* _idn,
              QString* _reference,
              QString* _manufacturer,
              int      _gpibAdd);

KeithleyK2400::KeithleyK2400();
KeithleyK2400::~KeithleyK2400();


double KeithleyK2400::getMaxVoltageSourceAtVoltageRange(double _vr)
{
    double result = 0;
    if      (_vr<0 || _vr>200)      result = -1;
    else if (_vr>=0 & _vr<0.2)      result = K2400_MAXVOLTAGESOURCE_AT_200mV_RANGE;
    else if (_vr>=0.2 & _vr<2)      result = K2400_MAXVOLTAGESOURCE_AT_2V_RANGE;
    else if (_vr>=2 & _vr<20)       result = K2400_MAXVOLTAGESOURCE_AT_20V_RANGE;
    else if (_vr>=20 & _vr<=200)    result = K2400_MAXVOLTAGESOURCE_AT_200V_RANGE;

    return result;
}
double KeithleyK2400::getMaxVoltageMeasureAtVoltageRange(double _vr)
{
    double result = 0;
    if      (_vr<0 || _vr>200)      result = -1;
    else if (_vr>=0 & _vr<0.2)      result = K2400_MAXVOLTAGEMEASURE_AT_200mV_RANGE;
    else if (_vr>=0.2 & _vr<2)      result = K2400_MAXVOLTAGEMEASURE_AT_2V_RANGE;
    else if (_vr>=2 & _vr<20)       result = K2400_MAXVOLTAGEMEASURE_AT_20V_RANGE;
    else if (_vr>=20 & _vr<=200)    result = K2400_MAXVOLTAGEMEASURE_AT_200V_RANGE;

    return result;
}
double KeithleyK2400::getVoltageComplianceAtVoltageRange(double _vr)
{
    double result = 0;
    if      (_vr<0 || _vr>200)      result = -1;
    else if (_vr>=0 & _vr<0.2)      result = K2400_COMPLIANCE_AT_200mV_RANGE;
    else if (_vr>=0.2 & _vr<2)      result = K2400_COMPLIANCE_AT_2V_RANGE;
    else if (_vr>=2 & _vr<20)       result = K2400_COMPLIANCE_AT_20V_RANGE;
    else if (_vr>=20 & _vr<=200)    result = K2400_COMPLIANCE_AT_200V_RANGE;

    return result;
}

double KeithleyK2400::getMaxCurrentSourceAtCurrentRange(double _cr)
{
    double result = 0;
    if      (_cr<0 || _cr>1)            result = -1;
    else if (_cr>=0 & _cr<1e-6)         result = K2400_MAXCURRENTSOURCE_AT_1uA_RANGE;
    else if (_cr>=1e-6 & _cr<10e-6)     result = K2400_MAXCURRENTSOURCE_AT_10uA_RANGE;
    else if (_cr>=10e-6 & _cr<100e-6)   result = K2400_MAXCURRENTSOURCE_AT_100uA_RANGE;
    else if (_cr>=100e-6 & _cr<1e-3)    result = K2400_MAXCURRENTSOURCE_AT_1mA_RANGE;
    else if (_cr>=1e-3 & _cr<10e-3)     result = K2400_MAXCURRENTSOURCE_AT_10mA_RANGE;
    else if (_cr>=10e-3 & _cr<100e-3)   result = K2400_MAXCURRENTSOURCE_AT_100mA_RANGE;
    else if (_cr>=100e-3 & _cr<=1)      result = K2400_MAXCURRENTSOURCE_AT_1A_RANGE;

    return result;
}
double KeithleyK2400::getMaxCurrentMeasureAtCurrentRange(double _cr)
{
    double result = 0;
    if      (_cr<0 || _cr>1)            result = -1;
    else if (_cr>=0 & _cr<1e-6)         result = K2400_MAXCURRENTMEASURE_AT_1uA_RANGE;
    else if (_cr>=1e-6 & _cr<10e-6)     result = K2400_MAXCURRENTMEASURE_AT_10uA_RANGE;
    else if (_cr>=10e-6 & _cr<100e-6)   result = K2400_MAXCURRENTMEASURE_AT_100uA_RANGE;
    else if (_cr>=100e-6 & _cr<1e-3)    result = K2400_MAXCURRENTMEASURE_AT_1mA_RANGE;
    else if (_cr>=1e-3 & _cr<10e-3)     result = K2400_MAXCURRENTMEASURE_AT_10mA_RANGE;
    else if (_cr>=10e-3 & _cr<100e-3)   result = K2400_MAXCURRENTMEASURE_AT_100mA_RANGE;
    else if (_cr>=100e-3 & _cr<=1)      result = K2400_MAXCURRENTMEASURE_AT_1A_RANGE;

    return result;
}
double KeithleyK2400::getCurrentComplianceAtCurrentRange(double _cr)
{
    double result = 0;
    if      (_cr<0 || _cr>1)            result = -1;
    else if (_cr>=0 & _cr<1e-6)         result = K2400_COMPLIANCE_AT_1uA_RANGE;
    else if (_cr>=1e-6 & _cr<10e-6)     result = K2400_COMPLIANCE_AT_10uA_RANGE;
    else if (_cr>=10e-6 & _cr<100e-6)   result = K2400_COMPLIANCE_AT_100uA_RANGE;
    else if (_cr>=100e-6 & _cr<1e-3)    result = K2400_COMPLIANCE_AT_1mA_RANGE;
    else if (_cr>=1e-3 & _cr<10e-3)     result = K2400_COMPLIANCE_AT_10mA_RANGE;
    else if (_cr>=10e-3 & _cr<100e-3)   result = K2400_COMPLIANCE_AT_100mA_RANGE;
    else if (_cr>=100e-3 & _cr<=1)      result = K2400_COMPLIANCE_AT_1A_RANGE;

    return result;
}

double KeithleyK2400::getAbsoluteMaxVoltage(){return K2400_ABSMAXVOLTAGE;}
double KeithleyK2400::getAbsoluteMaxPower(){return K2400_ABSMAXPOWER;}


QDomElement KeithleyK2400::toQDomElement()
{
    QDomDocument doc("MyML");

    QDomElement root = doc.createElement("KeithleyK2400");
    doc.appendChild(root);

    /*QDomElement nameTag = doc.createElement("name");
    root.appendChild(nameTag);

    QDomText nameText = doc.createTextNode(*getName());
    nameTag.appendChild(nameText);

    QDomElement idnTag = doc.createElement("idn");
    root.appendChild(idnTag);

    QDomText idnText = doc.createTextNode(*getIDN());
    idnTag.appendChild(idnText);

    QDomElement refTag = doc.createElement("reference");
    root.appendChild(refTag);

    QDomText refText = doc.createTextNode(*getReference());
    refTag.appendChild(refText);

    QDomElement manufactTag = doc.createElement("manufacturer");
    root.appendChild(manufactTag);

    QDomText manufactText = doc.createTextNode(*getManufacturer());
    manufactTag.appendChild(manufactText);

    QDomElement obsTag = doc.createElement("obsevations");
    root.appendChild(obsTag);

    QDomText obsText = doc.createTextNode(*getObs());
    obsTag.appendChild(obsText);*/

    return root;
}

void KeithleyK2400::print()
{
    std::cout<<"*******************************************"<<std::endl;
    std::cout<<"************KEITHLEY 2400 DATA*************"<<std::endl;
    std::cout<<"*******************************************"<<std::endl;
    KeithleyK24XX::print();
}


