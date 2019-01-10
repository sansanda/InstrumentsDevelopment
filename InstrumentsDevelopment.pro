#-------------------------------------------------
#
# Project created by QtCreator 2016-08-26T15:47:13
#
#-------------------------------------------------

QT       += core
QT       += widgets
#QT       -= gui
QT       += xml
QT       += testlib


# GPIB driver selection
# Uncomment proper driver selection
# Comment both for test mode only
CONFIG += adlink_usb
# CONFIG += ni_pci

TARGET = viewController
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    ../GPIB/gpib.cpp \
    ../GPIB/scpi.cpp \
    ../GPIB/SCPICommandFactory.cpp \
    ../Communications/parallelCommunications/gpib/gpibPort.cpp \
    ../Communications/serialCommunications/lan/lanport.cpp \
    ../Communications/serialCommunications/rs232/rs232.cpp \
    ../Communications/serialCommunications/usb/usbport.cpp \
    Instruments/keithley/sourceMeters/keithleyK2400.cpp \
    Instruments/keithley/sourceMeters/keithleyK2410.cpp \
    Instruments/keithley/sourceMeters/keithleyK2420.cpp \
    Instruments/keithley/sourceMeters/keithleyK2425.cpp \
    Instruments/keithley/sourceMeters/keithleyK2430.cpp \
    Instruments/keithley/sourceMeters/keithleyK2440.cpp \
    Instruments/keithley/sourceMeters/keithleyK24xx.cpp \
    Instruments/quadTech/LCRMeters/Q7600.cpp \
    Instruments/instrument.cpp \
    Instruments/InstrumentFactory.cpp \
    ../Communications/parallelCommunications/gpib/gpibPort2.cpp

OTHER_FILES += \
    ../GPIB/gpib-32.obj

HEADERS += \
    ../GPIB/Adgpib.h \
    ../GPIB/gpib.h \
    ../GPIB/gpib_user.h \
    ../GPIB/ni488.h \
    ../GPIB/scpi.h \
    ../GPIB/SCPICommandFactory.h \
    ../GPIB/callbackFunctions.h \
    ../Communications/parallelCommunications/gpib/gpibPort.h \
    ../Communications/parallelCommunications/parallelport.h \
    ../Communications/serialCommunications/lan/lanport.h \
    ../Communications/serialCommunications/rs232/rs232.h \
    ../Communications/serialCommunications/usb/usbport.h \
    ../Communications/serialCommunications/serialport.h \
    ../Communications/communicationPort.h \
    ../Maths/converters/numericalDataFormatConverter.h \
    ../Maths/dataFormat/floatingPointTools.h \
    ../Tools/bufferTools.h \
    Instruments/keithley/sourceMeters/K24xxConfigurationParameters.h \
    Instruments/keithley/sourceMeters/keithleyK2400.h \
    Instruments/keithley/sourceMeters/keithleyK2410.h \
    Instruments/keithley/sourceMeters/keithleyK2420.h \
    Instruments/keithley/sourceMeters/keithleyK2425.h \
    Instruments/keithley/sourceMeters/keithleyK2430.h \
    Instruments/keithley/sourceMeters/keithleyK2440.h \
    Instruments/keithley/sourceMeters/keithleyK24xx.h \
    Instruments/keithley/tools/keithleyTools.h \
    Instruments/quadTech/LCRMeters/Q7600.h \
    Instruments/gpibInstrument.h \
    Instruments/instrument.h \
    Instruments/instrumentFactory.h \
    Instruments/usbInstrument.h \
    ../Tools/debug.h \
    ../Communications/parallelCommunications/gpib/SRQEventListener.h \
    Instruments/commonTools/SRQEventListener.h \
    Instruments/commonTools/CMPLEventListener.h \
    ../testCMPLSignal.h \
    ../testSRQSignal.h \
    Instruments/commonTools/IBSTAMonitor.h \
    ../Communications/parallelCommunications/gpib/gpibPort2.h \
    Instruments/keithley/sourceMeters/KeithleyK24xxInterface.h

OTHER_FILES += \ gpib/gpib-32.obj

adlink_usb{
    # Driver's library setting
    CONFIG += ADLINK_USB_GPIB
    # Driver's includes
    DEFINES += AD_GPIB
}

win32:ADLINK_USB_GPIB {
    LIBS += $$quote(C:/ADLINK/ADL-GPIB/Lib/gpib-32.dll)
    LIBS += $$quote(C:/ADLINK/ADL-GPIB/Lib/gpib-32.lib)
}

win32:NI_PCI_GPIB {
    LIBS += gpib/gpib-32.obj
}

