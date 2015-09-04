#ifndef NETWORKTHREAD_H
#define NETWORKTHREAD_H
#include <QThread>
#include <QUdpSocket>
#include <QHostAddress>
#include "../qtkVirtualMIDI/qtkvirtualmidi.h"
#include "../qtkVirtualMIDI/qtkvirtualmidistructs.h"

#define MESSAGE_FIFO_SIZE 128

class networkThread : public QObject
{
    Q_OBJECT

public:
    networkThread(QHostAddress hostIp, quint16 udpPort, QObject *parent = 0);
    ~networkThread();    

private:
    QHostAddress m_hostIp;
    quint16 m_udpPort;
    QUdpSocket* p_socket;    
signals:

public slots:
    void OnMidiReceived(struct midiMessage message);

};

#endif // NETWORKTHREAD_H
