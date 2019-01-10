#include "./instruments/keithley/sourceMeters/keithleyK2440.h"


KeithleyK2440::KeithleyK2440(QString* _name,
              QString* _idn,
              QString* _reference,
              QString* _manufacturer,
              int      _gpibAdd);
KeithleyK2440::KeithleyK2440();
KeithleyK2440::~KeithleyK2440();

QDomElement KeithleyK2440::toQDomElement()
{
    QDomDocument doc("MyML");

    QDomElement root = doc.createElement("KeithleyK2440");
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

void KeithleyK2440::print()
{
    std::cout<<"*******************************************"<<std::endl;
    std::cout<<"************KEITHLEY 2400 DATA*************"<<std::endl;
    std::cout<<"*******************************************"<<std::endl;
    KeithleyK24XX::print();
}
