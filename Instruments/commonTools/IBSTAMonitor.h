#ifndef IBSTAMONITOR_H
#define IBSTAMONITOR_H


#include <QObject>
#include <QDebug>
#include <QThread>
#include "../Communications/parallelCommunications/gpib/gpibPort2.h"

#include "../GPIB/gpib_user.h"
#include "stdio.h"
#include "../Tools/debug.h"

class IBSTAMonitor:public QThread{

    Q_OBJECT

public:
    IBSTAMonitor(){gpibInstrumentHandler = -1;}
    ~IBSTAMonitor(){}

    int getGpibInstrumentHandler() const {return gpibInstrumentHandler;}
    void setGpibInstrumentHandler(int value) {gpibInstrumentHandler = value;}

    void checkIBSTA()
    {
        int  ibsta = 0;
        qDebug()<<"**********************************************";
        while (true){ /*true*/
            QThread::msleep(1000);

            ibsta = GPIBPort2::waitForResponse(gpibInstrumentHandler,0);


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


        }

    }
    void run()
    {
        checkIBSTA();
    }

signals:
    void SRQDetectedSignal();

private:
    int gpibInstrumentHandler;

};
#endif // IBSTAMONITOR_H
