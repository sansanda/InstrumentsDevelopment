#include "./instruments/quadTech/LCRMeters/Q7600.h"


int Q7600::getGPIBAddress() {return gpibPort->getAddress();}
int Q7600::setGPIBAddress(int newAddress){gpibPort->setAddress(newAddress);}
int Q7600::test(){

    int result = 0;
    int delay = 100;

    //Test que permite evaluar el resultado de la ejecución de comandos


    std::cout<<"*******************************************"<<std::endl;
    std::cout<<"*****CONFIGURING THE TEST*****************"<<std::endl;
    std::cout<<"*******************************************"<<std::endl;
    std::cout<<"\n"<<std::endl;

   //Insert here the commands you want to test

    QString c = "*RST";
    gpibPort->testInstrunction("*RST");
    QThread::sleep(delay*10);



    return result;

}
