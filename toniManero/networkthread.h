#ifndef NETWORKTHREAD_H
#define NETWORKTHREAD_H
#include <QThread>
#include <QUdpSocket>
#include <QHostAddress>
#include "../qtkVirtualMIDI/qtkvirtualmidistructs.h"

class networkThread : public QThread
{
    Q_OBJECT

public:
    networkThread(quint16 udpPort);
    ~networkThread();
    QUdpSocket* getUdpSocket();
    void run();

private:    
    char* midiMessageToStr(struct midiMessage* message);
    quint16 m_udpPort;
    QUdpSocket* p_socket;    

signals:
    void midiUpdate(struct midiMessage message);

public slots:
    void OnReadyRead();

};

#endif // NETWORKTHREAD_H
