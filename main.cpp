#include <QApplication>
#include "Instruments/keithley/sourceMeters/keithleyK2400.h"
#include "../GPIB/Adgpib.h"
#include "../testCMPLSignal.h"
#include "../testSRQSignal.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    TestCMPLSignal* ts;
    ts = new TestCMPLSignal();
    ts->test();

//    TestSRQSignal* tsrq;
//    tsrq = new TestSRQSignal();
//    tsrq->test();

//    KeithleyK2400* k2400;
//    k2400 = new KeithleyK2400(new QString(""),new QString(""),new QString(""),new QString(""));
//    k2400->setGPIBAddress(21);
//    k2400->openConnection();
//    k2400->ibstaMonitor->start();
//    QThread::msleep(3000);
//    k2400->enableOutput();
//    k2400->configureStandardEventStatusEnableRegister(1);
//    k2400->configureServiceRequestEnableRegister(16); // enable mav bit
//    k2400->sendOPCCommand();

/*
    KeithleyK2400* k2400;
    k2400 = new KeithleyK2400(new QString(""),new QString(""),new QString(""),new QString(""));
    k2400->setGPIBAddress(21);
    k2400->openConnection();
    QThread::msleep(10);
    k2400->reset();
    QThread::msleep(100);
    k2400->configAsVoltageSource();
    QThread::msleep(10);
    k2400->setVoltageSourceRange(1);
    QThread::msleep(10);
    k2400->setVoltageSourceLevel(0.1);
    QThread::msleep(10);
    k2400->configAsCurrentMeasure();
    QThread::msleep(10);
    k2400->setCurrentMeasureCompliance(0.1);
    QThread::msleep(10);
    k2400->setCurrentMeasureRange(0.1);
    QThread::msleep(10);
    k2400->redirectOutputToFront();
    QThread::msleep(10);
    k2400->configTimeStampAsAbsolute();
    QThread::msleep(10);

    //k2400->enableOutput();
    QThread::msleep(10);

    //qDebug()<<"Voltage = "<<k2400->readVoltage();
    //qDebug()<<"Current = "<<k2400->readCurrent();
    //qDebug()<<"Mean Voltage (10) = "<<k2400->readMeanVoltage(10);
    //qDebug()<<"Mean Current (10) = "<<k2400->readMeanCurrent(10);
//    while (true){
//        QThread::msleep(1000);
//        qDebug()<<"Voltage = "<<k2400->readVoltage()<<", Current = "<<k2400->readCurrent();
//    }

    //k2400->gpibPort->clearDevice();
    //QThread::msleep(1000);

    QThread::msleep(10);
    qDebug()<<k2400->gpibPort->setTimeout(TNONE);

    k2400->enableOutput();
    k2400->setMeasureDelay(1);

    k2400->readVoltageAsynchronously();
*/


    qDebug()<<"Holaaaaa ";

    return a.exec();
}
