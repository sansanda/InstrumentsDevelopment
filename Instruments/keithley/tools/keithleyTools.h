#ifndef KEITHLEYTOOLS_H
#define KEITHLEYTOOLS_H

#include "./Instruments/keithley/sourceMeters/K24xxConfigurationParameters.h"
#include "./Instruments/keithley/sourceMeters/keithleyK24xx.h"
#include "../Maths/converters/numericalDataFormatConverter.h"
#include <QDebug>

class TriggerCountBuffer {

public:
    TriggerCountBuffer(){}
    ~TriggerCountBuffer(){}


    void getMeasureNumber(int number,char *measure)
    {
        int offset = 2;
        for (int i=0;i<4;i++)
        {
            #ifndef DEBUG
                qDebug() << "index = " <<4*number+offset+i;
            #endif
            measure[3-i] = buffer[4*number+offset+i];
        }
    }
    void printBufferContent(int size){
        for (int i=0;i<size;i++) {
            qDebug() << (int)buffer[i]<<endl;
        }
    }
    void printMeasure(int measureNumber){
        char measure[4] = {0,0,0,0};
        getMeasureNumber(measureNumber,measure);
        qDebug() <<  " measure "<< measureNumber << " = " <<NumericalDataFormatConverter::singlePrecisionDataFormatToDouble(measure);
    }
    void printMeasures(int begin, int end){
        for (int i=begin;i<end;i++)
        {
            printMeasure(i);
        }
    }
    void printAllMeasures(int end){
        for (int i=0;i<end;i++)
        {
            printMeasure(i);
        }
    }
    void printAllMeasuresBufferContent(){
        for (int i=0;i<READBUFFER_SIZE_MAX;i++)
        {
            printMeasure(i);
        }
    }
private:

public:
    char buffer[READBUFFER_SIZE_MAX];


protected:


};
class InternalDataBuffer {

public:
    InternalDataBuffer(){}
    ~InternalDataBuffer(){}

    void getMeasureNumber(int number,char *measure)
    {
        int offset = 2;
        for (int i=0;i<4;i++)
        {
            #ifndef DEBUG
                qDebug() << "index = " <<4*number+offset+i;
            #endif
            measure[3-i] = buffer[4*number+offset+i];
        }
    }
    void printBufferContent(int size){
        for (int i=0;i<size;i++) {
            qDebug() << (int)buffer[i]<<endl;
        }
    }


private:

public:
    char buffer[READBUFFER_SIZE_MAX];

protected:


};

#endif // KEITHLEYTOOLS_H
