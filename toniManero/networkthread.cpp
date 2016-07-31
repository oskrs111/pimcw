#include "networkthread.h"
#include <QDebug>

networkThread::networkThread(quint16 udpPort)
{    
    this->m_udpPort = udpPort;
    this->p_socket = 0;
}

networkThread::~networkThread()
{
    if(this->p_socket)
    {
        this->p_socket->deleteLater();
    }
}

QUdpSocket* networkThread::getUdpSocket()
{
    return this->p_socket;
}

void networkThread::run()
{

    this->p_socket->moveToThread(this);
    this->exec();
}

void networkThread::OnReadyRead()
{
    QByteArray data;
    QHostAddress sender;
    quint16 senderPort;
    qint64 pendingSize;

    struct midiMessage message;

    if(this->p_socket)
    {
        char* p = 0;
        pendingSize = this->p_socket->pendingDatagramSize();
        data.fill(0x00, pendingSize);
        this->p_socket->readDatagram(data.data(),
                                     data.size(),
                                     &sender,
                                     &senderPort);

        p = data.data();
        for(int t = 0; t < data.size(); t++)
        {
            memset(&message, 0x00, sizeof(message));
            memcpy(&message, p, sizeof(struct midiMessage));
            t += sizeof(struct midiMessage);
            p += sizeof(struct midiMessage);
            emit this->midiUpdate(message);
            qDebug() << this->midiMessageToStr(&message);
        }
    }
}

char* networkThread::midiMessageToStr(struct midiMessage* message)
{
    static char dumpBuffer[1024];
    sprintf(dumpBuffer, "%s, channel=%02d, Data1=%03d, Data2=%03d",
            status2string[message->m_status],
            message->m_channel,
            message->m_data1,
            message->m_data2);

    return dumpBuffer;
}


