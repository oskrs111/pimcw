#include <QThread>
#include "main.h"
#include "pca9685interface.h"

void debugLogger(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    switch (type) {
    case QtDebugMsg:
        localMsg.prepend("DEBUG: ");
        fprintf(stderr, "Debug: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtWarningMsg:
        localMsg.prepend("WARNING: ");
        fprintf(stderr, "Warning: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtCriticalMsg:
        localMsg.prepend("CRITICAL: ");
        fprintf(stderr, "Critical: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtFatalMsg:
        localMsg.prepend("FATAL: ");
        fprintf(stderr, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        abort();
    }

    localMsg.append("\r\n");

    QFile f("debug.log");
    f.open(QIODevice::Append);
    f.write(localMsg);
    f.close();
}

static QtKApplicationParameters* g_appParameters = 0;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qDebug() << "toniManero starting...";

    g_appParameters = new QtKApplicationParameters(0,QString("discoFever"));

    if(g_appParameters->fileLoad(false))
    {
            setDefaultParameters();
            QString msg = "discoFever.cfg not found!\r\nSetting default configuration.";
            qDebug() << msg;
            a.exit();
    }

    if(!g_appParameters->loadParam(QString("aplicacion"),QString("fileLog"),0).compare("1"))
    {
        qInstallMessageHandler(debugLogger);
    }

    //http://stackoverflow.com/questions/19375141/udp-packet-is-not-received-in-qthread

    pca9685Interface interface((quint16)g_appParameters->loadParam(QString("network"),QString("udpPort"),0).toInt(),
                               (quint8)g_appParameters->loadParam(QString("i2c"),QString("i2cBus"),0).toInt(),
                               (quint8)g_appParameters->loadParam(QString("i2c"),QString("i2cAddr"),0).toInt(),
                               (quint8)g_appParameters->loadParam(QString("midi"),QString("noteOffset"),0).toInt());


    qDebug() << "toniManero is dancing now!";

    while(1)
    {
        interface.socketPoll();
        QThread::usleep(1);
    }
    return a.exec();
}

void setDefaultParameters()
{
    g_appParameters->saveParam(QString("app"),QString("fileLog"),QString("0"));    
    g_appParameters->saveParam(QString("i2c"),QString("i2cBus"),QString("1"));
    g_appParameters->saveParam(QString("i2c"),QString("i2cAddr"),QString("64"));
    g_appParameters->saveParam(QString("network"),QString("udpPort"),QString("12340"));
    g_appParameters->saveParam(QString("midi"),QString("noteOffset"),QString("0"));
    g_appParameters->fileSave();
}