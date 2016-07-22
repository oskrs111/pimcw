#ifndef NETWORKTHREAD_H
#define NETWORKTHREAD_H
#include <QThread>
#include <QUdpSocket>
#include <QHostAddress>
#include "../qtkVirtualMIDI/qtkvirtualmidi.h"
#include "../qtkVirtualMIDI/qtkvirtualmidistructs.h"

class networkThread : public QThread
{
    Q_OBJECT

public:
    networkThread(QHostAddress hostIp,
                  quint16 udpPort,
                  quint8 statusRepeat,
                  quint8 midiOffIgnore,
                  quint8 midiChannelFilter,
                  quint8 midiChannelFilterEnable,
                  quint8 midiNoteOffset);

    ~networkThread();
    void run();

private:
    QHostAddress m_hostIp;
    quint16 m_udpPort;
    quint8 m_statusRepeat;
    quint8 m_midiOffIgnore;
    quint8 m_midiChannelFilter;
    quint8 m_midiChannelFilterEnable;
    quint8 m_midiNoteOffset;
    QUdpSocket* p_socket;    
signals:

public slots:
    void OnMidiReceived(struct midiMessage message);

};

#endif // NETWORKTHREAD_H
