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
    ../qtkApplicationParameters/qtkapplicationparameters.cpp \
    ../qtkVirtualMIDI/qtkvirtualmidi.cpp \
    networkthread.cpp

HEADERS += main.h \
        teVirtualMIDI.h \
    ../qtkApplicationParameters/qtkapplicationparameters.h \
    ../qtkVirtualMIDI/qtkvirtualmidi.h \
    networkthread.h \
    ../qtkVirtualMIDI/qtkvirtualmidistructs.h

INCLUDEPATH += "../teVirtualMIDISDK_1_1_2_25/C" \
            "../qtkApplicationParameters"

LIBS += -L"../teVirtualMIDISDK_1_1_2_25/C" -lteVirtualMIDI32
