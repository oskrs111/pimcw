#include "networkthread.h"
#include <QDebug>

networkThread::networkThread(QHostAddress hostIp,
                             quint16 udpPort,
                             quint8 statusRepeat,
                             quint8 midiOffIgnore,
                             quint8 midiChannelFilter,
                             quint8 midiChannelFilterEnable,
                             quint8 midiNoteOffset)
{
    this->m_hostIp = hostIp;
    this->m_udpPort = udpPort;
    this->m_statusRepeat = statusRepeat;
    this->m_midiOffIgnore = midiOffIgnore;
    this->m_midiChannelFilter = midiChannelFilter;
    this->m_midiChannelFilterEnable = midiChannelFilterEnable;
    this->m_midiNoteOffset = midiNoteOffset;

    if(this->m_midiChannelFilter >= 16) this->m_midiChannelFilter = 15;
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
    if((this->m_midiOffIgnore > 0) && (message.m_status == MM_NOTE_OFF)) return;
    if((this->m_midiChannelFilterEnable > 0) && (this->m_midiChannelFilter == message.m_channel)) return;    
    if((message.m_status == MM_NOTE_ON) || (message.m_status == MM_NOTE_OFF)) message.m_data1 -= this->m_midiNoteOffset;

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

