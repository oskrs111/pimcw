#-------------------------------------------------
#
# Project created by QtCreator 2015-08-19T08:58:33
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = discoFever
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

DEFINES += VEJAM_NO_GUI

SOURCES += main.cpp \
    ../../qtkApplicationParameters/qtkapplicationparameters.cpp \
    ../../qtkVirtualMIDI/qtkvirtualmidi.cpp \
    networkthread.cpp


HEADERS += main.h \
    ../../qtkApplicationParameters/qtkapplicationparameters.h \
    ../../qtkVirtualMIDI/qtkvirtualmidi.h \
    networkthread.h \
    ../qtkVirtualMIDI/qtkvirtualmidistructs.h

INCLUDEPATH += "../../qtkApplicationParameters"

#--Tobias Erichsen\teVirtualMIDISDK--
HEADERS += "C:\Program Files (x86)\Tobias Erichsen\teVirtualMIDISDK\C-Binding\teVirtualMIDI.h"
INCLUDEPATH += "C:/Program Files (x86)/Tobias Erichsen/teVirtualMIDISDK/C-Binding"
LIBS += -L"C:/Program Files (x86)/Tobias Erichsen/teVirtualMIDISDK/C-Binding" -lteVirtualMIDI32

