#ifndef MAIN_H
#define MAIN_H
#include <QCoreApplication>
#include <QMessageLogContext>
#include <QFile>
#include <QDebug>
#include "qtkapplicationparameters.h"

#define DISCOFEVER_APP_VERSION "BETA 1.0"

//http://doc.qt.io/qt-5/qtglobal.html#qInstallMessageHandler
void debugLogger(QtMsgType type, const QMessageLogContext &context, const QString &msg);
void setDefaultParameters();
#endif // MAIN_H
