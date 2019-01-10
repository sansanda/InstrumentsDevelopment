#ifndef CMPLEVENTLISTENER_H
#define CMPLEVENTLISTENER_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include "../Communications/parallelCommunications/gpib/gpibPort2.h"

#include "../GPIB/gpib_user.h"
#include "stdio.h"
#include "../Tools/debug.h"

class CMPLEventListener:public QThread{

    Q_OBJECT

public:
    CMPLEventListener(){gpibInstrumentHandler = -1;}
    ~CMPLEventListener(){}

    int getGpibInstrumentHandler() const {return gpibInstrumentHandler;}
    void setGpibInstrumentHandler(int value) {gpibInstrumentHandler = value;}


    void waitForCMPLSignal()
    {
        #if DEBUG_GPIBPORT==1
            qDebug()<<"Waiting for the CMPL Event.....";
        #endif
        bool CMPLDetected = false;
        int  ibsta = 0;
        while (!CMPLDetected){ /*true*/
            QThread::msleep(5);
            ibsta = GPIBPort2::waitForResponse(gpibInstrumentHandler,0);

            #if DEBUG_GPIBPORT == 1
                if ((ibsta >> ERR_NUM) & 0x0001) qDebug()<< (" ERR");
                if ((ibsta >> TIMO_NUM) & 0x0001) qDebug()<< (" TIMO");
                if ((ibsta >> END_NUM) & 0x0001) qDebug()<< (" END");
                if ((ibsta >> SRQI_NUM) & 0x0001) qDebug()<< (" SRQI");
                if ((ibsta >> RQS_NUM) & 0x0001) qDebug()<< (" RQS");
                if ((ibsta >> CMPL_NUM) & 0x0001) qDebug()<< (" CMPL");
                if ((ibsta >> LOK_NUM) & 0x0001) qDebug()<< (" LOK");
                if ((ibsta >> REM_NUM) & 0x0001) qDebug()<< (" REM");
                if ((ibsta >> CIC_NUM) & 0x0001) qDebug()<< (" CIC");
                if ((ibsta >> ATN_NUM) & 0x0001) qDebug()<< (" ATN");
                if ((ibsta >> TACS_NUM) & 0x0001) qDebug()<< (" TACS");
                if ((ibsta >> LACS_NUM) & 0x0001) qDebug()<< (" LACS");
                if ((ibsta >> DTAS_NUM) & 0x0001) qDebug()<< (" DTAS");
                if ((ibsta >> DCAS_NUM) & 0x0001) qDebug()<< (" DCAS");
            #endif


            #if DEBUG_GPIBPORT == 1
                qDebug()<<ibsta;
            #endif
            ibsta = ibsta >> CMPL_NUM ;
            #if DEBUG_GPIBPORT == 1
                qDebug()<<ibsta;
            #endif
            ibsta = ibsta & 0x0001;
            #if DEBUG_GPIBPORT == 1
                qDebug()<<ibsta;
            #endif
            if (ibsta == 1) CMPLDetected = true;
        }
        #if DEBUG_GPIBPORT==1
            qDebug()<<"CMPL Detected..............";
        #endif

    }
    void run()
    {
        #if DEBUG_GPIBPORT==1
            qDebug()<<"Starting the CMPL Listener.....";
        #endif
        waitForCMPLSignal();
        emit CMPLDetectedSignal();
        #if DEBUG_GPIBPORT==1
            qDebug()<<"CMPL Signal emited..............";
        #endif

    }

signals:
    void CMPLDetectedSignal();

private:
    int gpibInstrumentHandler;
};
#endif // CMPLEVENTLISTENER_H

