#include "./instruments/instrumentFactory.h"
#include <iostream>


InstrumentFactory::InstrumentFactory (){}
InstrumentFactory::~InstrumentFactory(){}

Instrument* InstrumentFactory::createInstrument(int instrumentType){

    Instrument* i;
    switch(instrumentType)
    {
    case K2400:
    {
        std::cout<<"INSTRUMENT FACTORY: Creating K2400 Instrument"<<std::endl;
        i = new KeithleyK2400();
    break;
    }
    case K2410:
    {
        std::cout<<"INSTRUMENT FACTORY: Creating K2410 Instrument"<<std::endl;
        i = new KeithleyK2410();
    break;
    }
    case K2420:
    {
        std::cout<<"INSTRUMENT FACTORY: Creating K2420 Instrument"<<std::endl;
        i = new KeithleyK2420();
    break;
    }
    case K2425:
    {
        std::cout<<"INSTRUMENT FACTORY: Creating K2425 Instrument"<<std::endl;
        i = new KeithleyK2425();
    break;
    }
    case K2430:
    {
        std::cout<<"INSTRUMENT FACTORY: Creating K2430 Instrument"<<std::endl;
        i = new KeithleyK2430();
    break;
    }
    case QUADTECH7600:
    {
        std::cout<<"INSTRUMENT FACTORY: Creating QUADTECH7600 Instrument"<<std::endl;
        //TODO: Add the quadtech 7600 instrument i = new .....;

    break;
    }
    default:
    {
        std::cout<<"INSTRUMENT FACTORY: Creating K2400 Instrument by default"<<std::endl;
        i = new KeithleyK2400();
    break;
    }
        return i;
    }
}
