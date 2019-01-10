#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include <QObject>
#include "iostream"
#include <QThread>

class Instrument: public QObject{
    Q_OBJECT

public:
    Instrument(         QString* _name,
                        QString* _idn,
                        QString* _reference,
                        QString* _manufacturer)
    {
        setName(_name);
        setIDN(_idn);
        setReference(_reference);
        setManufacturer(_manufacturer);
    }
    Instrument()
    {
        setName(new QString("default Name"));
        setIDN(new QString("default IDN"));
        setReference(new QString("default reference"));
        setManufacturer(new QString("default manufacturer"));
    }

    ~Instrument(){}

    QString* getName(){return name;}
    void setName(QString* _name){name = _name;}
    QString* getIDN(){return idn;}
    void setIDN(QString* _idn){idn = _idn;}
    QString* getReference(){return reference;}
    void setReference(QString* _reference){reference = _reference;}
    QString* getManufacturer(){return manufacturer;}
    void setManufacturer(QString* _manufacturer){manufacturer = _manufacturer;}


    void print()
    {


        std::cout<<"*******************************************"<<std::endl;
        std::cout<<"**************INSTRUMENT DATA**************"<<std::endl;
        std::cout<<"*******************************************"<<std::endl;

        std::cout<<"Name = "        <<getName()->toStdString()<<std::endl;
        std::cout<<"IDN = "         <<getIDN()->toStdString()<<std::endl;
        std::cout<<"Reference = "   <<getReference()->toStdString()<<std::endl;
        std::cout<<"Manufacturer = "<<getManufacturer()->toStdString()<<std::endl;
    }


protected:


private:
    QString*    name;
    QString*    idn;
    QString*    reference;
    QString*    manufacturer;

};


#endif // INSTRUMENT_H
