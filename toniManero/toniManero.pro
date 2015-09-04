#-------------------------------------------------
#
# Project created by QtCreator 2015-08-19T08:58:33
#
#-------------------------------------------------
#http://doc.qt.io/qt-5/qmake-project-files.html

QT       += core network

QT       -= gui

TARGET = toniManero
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

target.path = /opt
INSTALLS += target

DEFINES += VEJAM_NO_GUI

unix {
#this is the configuration need to compile for raspberry pi B+
    CONFIG += static
    DEFINES += USE_I2C_BUS
    DEFINES += USE_LINUX_PLATFORM
    LIBS += -lqeglfs -L/mnt/rasp-pi-rootfs/usr/local/QtPi5.4.2/plugins/platforms/
    LIBS += -lqico -L/mnt/rasp-pi-rootfs/usr/local/QtPi5.4.2/plugins/imageformats/
    LIBS += -lqconnmanbearer -L/mnt/rasp-pi-rootfs/usr/local/QtPi5.4.2/plugins/bearer/
    LIBS += -lqgenericbearer -L/mnt/rasp-pi-rootfs/usr/local/QtPi5.4.2/plugins/bearer/
    LIBS += -lqnmbearer -L/mnt/rasp-pi-rootfs/usr/local/QtPi5.4.2/plugins/bearer/    
}

win32 {
RC_ICONS += toniManero.ico
}

SOURCES += main.cpp \    
    pca9685interface.cpp \
    networkthread.cpp \
    ../qtkApplicationParameters/qtkapplicationparameters.cpp \
    ../qtkHttpServer/qtkHttpServer.cpp \
    ../qtkHttpServer/qtkJsRpcServer.cpp \
    ../qtkHttpServer/qtkRtpCommand_.cpp


HEADERS += main.h \        
    pca9685interface.h \
    networkthread.h \
    ../qtkApplicationParameters/qtkapplicationparameters.h \        
    ../qtkVirtualMIDI/qtkvirtualmidistructs.h \    
    ../qtkHttpServer/qtkHttpCommon.h \
    ../qtkHttpServer/qtkHttpServer.h \
    ../qtkHttpServer/qtkJsRpcServer.h \
    ../qtkHttpServer/qtkRtpCommand_.h \
    ../config/qtkHttpServerConfig.h \
    ../rpcCommands/qtkRtpCommand_headers.h \
    ../rpcCommands/qtkRtpCommand_id.h \
    ../rpcCommands/qtkRtpCommand_PwmSet.h \
    ../rpcCommands/qtkRtpCommandsInit.h \
    ../rpcCommands/qtkRtpCommand_Test.h \
    ../rpcCommands/qtkRtpCommand_headers.h \
    ../rpcCommands/qtkRtpCommand_id.h \
    ../rcpCommands/qtkRtpCommand_PwmSet.h \
    ../rpcCommands/qtkRtpCommand_Test.h \
    ../rpcCommands/qtkRtpCommandsInit.h


INCLUDEPATH += "../qtkApplicationParameters" \
               "../qtkHttpServer" \
               "../config" \
               "../rpcCommands"
