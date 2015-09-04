#include "networkthread.h"
#include <QDebug>

networkThread::networkThread(QHostAddress hostIp, quint16 udpPort, QObject *parent) : QObject(parent)
{
    this->m_hostIp = hostIp;
    this->m_udpPort = udpPort;
    this->p_socket = 0;

    if(this->m_hostIp.isNull() == false)
    {
        qDebug() << "networkThread ip host: " << this->m_hostIp;
        qDebug() << "networkThread udp port: " << this->m_udpPort;
        this->p_socket = new QUdpSocket(this);
    }
}

networkThread::~networkThread()
{
    if(this->p_socket)
    {
        this->p_socket->deleteLater();
    }
}

void networkThread::OnMidiReceived(struct midiMessage message)
{
    //qDebug() << "OnMidiReceived, message: " << qtkVirtualMIDI::binToStr((unsigned char*)&message, sizeof(message));
    qDebug() << qtkVirtualMIDI::midiMessageToStr(&message);

    if(this->p_socket)
    {
        this->p_socket->writeDatagram((char*)&message, sizeof(struct midiMessage), this->m_hostIp, this->m_udpPort);
        this->p_socket->flush();
    }
}

