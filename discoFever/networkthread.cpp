#include "networkthread.h"
#include <QDebug>

networkThread::networkThread(QHostAddress hostIp, quint16 udpPort, quint8 statusRepeat)
{
    this->m_hostIp = hostIp;
    this->m_udpPort = udpPort;
    this->m_statusRepeat = statusRepeat;
    if(this->m_statusRepeat == 0) this->m_statusRepeat = 1;

    this->p_socket = 0;
}

networkThread::~networkThread()
{
    if(this->p_socket)
    {
        this->p_socket->deleteLater();
    }
}

void networkThread::run()
{
    qDebug() << "networkThread id: " << currentThreadId();
    if(this->m_hostIp.isNull() == false)
    {
        qDebug() << "networkThread ip host: " << this->m_hostIp;
        qDebug() << "networkThread udp port: " << this->m_udpPort;
        this->p_socket = new QUdpSocket();
        this->exec();
    }
}

void networkThread::OnMidiReceived(struct midiMessage message)
{
    static quint8 index = 0;
    quint8 t = 0;
    //qDebug() << "OnMidiReceived, message: " << qtkVirtualMIDI::binToStr((unsigned char*)&message, sizeof(message));
    qDebug() << qtkVirtualMIDI::midiMessageToStr(&message);

    if(this->p_socket)
    {
        message.m_index = index;
        for(t = 0; t < this->m_statusRepeat; t++)
        {
            this->p_socket->writeDatagram((char*)&message, sizeof(struct midiMessage), this->m_hostIp, this->m_udpPort);
            this->p_socket->flush();
        }
        index++;
    }
}

