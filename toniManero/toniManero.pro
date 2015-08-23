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
#this is the configuration need to compile for raspberry pi B+
    CONFIG += static
    DEFINES += USE_I2C_BUS
    LIBS += -lqeglfs -L/mnt/rasp-pi-rootfs/usr/local/QtPi5.4.2/plugins/platforms/
    LIBS += -lqico -L/mnt/rasp-pi-rootfs/usr/local/QtPi5.4.2/plugins/imageformats/
    LIBS += -lqconnmanbearer -L/mnt/rasp-pi-rootfs/usr/local/QtPi5.4.2/plugins/bearer/
    LIBS += -lqgenericbearer -L/mnt/rasp-pi-rootfs/usr/local/QtPi5.4.2/plugins/bearer/
    LIBS += -lqnmbearer -L/mnt/rasp-pi-rootfs/usr/local/QtPi5.4.2/plugins/bearer/
}

SOURCES += main.cpp \
    ../qtkApplicationParameters/qtkapplicationparameters.cpp \        
    pca9685interface.cpp

HEADERS += main.h \        
    ../qtkApplicationParameters/qtkapplicationparameters.h \        
    ../qtkVirtualMIDI/qtkvirtualmidistructs.h \
    pca9685interface.h

INCLUDEPATH += "../qtkApplicationParameters"