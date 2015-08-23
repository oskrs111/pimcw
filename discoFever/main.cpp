#include "main.h"
#include "networkthread.h"
#include "../qtkVirtualMIDI/qtkvirtualmidi.h"

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
    qDebug() << "discoFever starting...";

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

    qtkVirtualMIDI midi;
    networkThread network(QHostAddress(g_appParameters->loadParam(QString("network"),QString("udpHost"),0)),
                          g_appParameters->loadParam(QString("network"),QString("udpPort"),0).toInt());

    switch(midi.getStatus())
    {
        case stReady:
            QObject::connect(&midi,SIGNAL(midiReceived(midiMessage)),&network, SLOT(OnMidiReceived(midiMessage)));
            network.start();
            qDebug() << "discoFever is ready to dance!";
            return a.exec();
            break;

        case stUnknown:
        case stClosed:
        case stError:
        default:
            qDebug() << "qtkVirtualMIDI error, status: " << midi.getStatus();
            qDebug() << "discoFever will exit now...";
            break;
    }

    return 0;
}

void setDefaultParameters()
{
    g_appParameters->saveParam(QString("app"),QString("fileLog"),QString("0"));
    g_appParameters->saveParam(QString("network"),QString("udpHost"),QString("192.168.0.100"));
    g_appParameters->saveParam(QString("network"),QString("udpPort"),QString("12340"));    
    g_appParameters->fileSave();
}