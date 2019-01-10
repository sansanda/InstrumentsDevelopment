#ifndef USBINSTRUMENT_H
#define USBINSTRUMENT_H

#include "./instruments/instrument.h"

class USBInstrument: public Instrument{

public:
    USBInstrument(     QString* _name,
                        QString* _idn,
                        QString* _reference,
                        QString* _manufacturer,
                        int _usbPort     ):Instrument(_name,_idn,_reference,_manufacturer)
    {
        setUSBPort(_usbPort);
    }
    USBInstrument():Instrument() {setUSBPort(0);}

    ~USBInstrument(){}

    int         getUSBPort()                                {return usbPort;}
    void        setUSBPort(int _usbPort)                    {usbPort = _usbPort;}

    void print()
    {


        std::cout<<"*******************************************"<<std::endl;
        std::cout<<"************USB INSTRUMENT DATA***********"<<std::endl;
        std::cout<<"*******************************************"<<std::endl;

        Instrument::print();
        std::cout<<"USB Port = "   <<getUSBPort()<<std::endl;
    }


protected:


private:

    int         usbPort;

};


#endif // USBINSTRUMENT_H
