#-------------------------------------------------
#
# Project created by QtCreator 2015-08-19T08:58:33
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = toniManero
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

DEFINES += VEJAM_NO_GUI

linux
{
#    DEFINES += USE_I2C_BUS
}

SOURCES += main.cpp \
    ../qtkApplicationParameters/qtkapplicationparameters.cpp \        
    pca9685interface.cpp

HEADERS += main.h \        
    ../qtkApplicationParameters/qtkapplicationparameters.h \        
    ../qtkVirtualMIDI/qtkvirtualmidistructs.h \
    pca9685interface.h

INCLUDEPATH += "../qtkApplicationParameters"
