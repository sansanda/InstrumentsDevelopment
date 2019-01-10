#ifndef Q7600_H
#define Q7600_H

#include "../Communications/parallelCommunications/gpib/gpibPort.h"
#include "./Instruments/instrument.h"

class Q7600: public Instrument{

public:
    Q7600(             QString* _name,
                       QString* _idn,
                       QString* _reference,
                       QString* _manufacturer):Instrument(_name,_idn,_reference,_manufacturer)
    {

        gpibPort = new GPIBPort();
    }
    Q7600():Instrument()
    {
        gpibPort = new GPIBPort();
    }
    ~Q7600(){}





    int openConnection();
    int checkPresence();
    QString getIDN();



    //Communications
    int getGPIBAddress();
    int setGPIBAddress(int newAddress);

    //Others
    int testCommand(QString comm);


    //Test
    int test();

    void print()
    {

        Instrument::print();

        std::cout<<"*******************************************"<<std::endl;
        std::cout<<"***************Q7600 2400 DATA*************"<<std::endl;
        std::cout<<"*******************************************"<<std::endl;

    }

private:


public:
    //Communication Ports
    GPIBPort* gpibPort;


protected:


};
#endif // Q7600_H
