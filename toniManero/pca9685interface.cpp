#include "pca9685interface.h"
#include <QDebug>
#include <QThread>

#ifdef USE_I2C_BUS
extern "C"
{
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
}
#endif

pca9685Interface::pca9685Interface(quint16 udpPort, , quint8 i2cBus, quint8 i2cAddr, quint8 noteOffset, QObject *parent) : QObject(parent)
{
    this->m_udpPort = udpPort;
    this->m_i2cBus = i2cBus;
    this->m_i2cAddr = i2cAddr;
    this->m_noteOffset = noteOffset;
    this->m_i2cHandler = 0;

    this->networkInit();
    if(this->i2cInit() == 0)
    {
        this->pwmInit();
    }
}

pca9685Interface::~pca9685Interface()
{
    if(this->p_socket) this->p_socket->deleteLater();
}

void pca9685Interface::networkInit()
{
    this->p_socket = new QUdpSocket(this);
    this->p_socket->bind(QHostAddress::Any, this->m_udpPort);
    qDebug() << "pca9685Interface listening on udp port: " << this->m_udpPort;
}

int pca9685Interface::i2cInit()
{
#ifdef USE_I2C_BUS
    char deviceName[32];

    snprintf(deviceName, sizeof(deviceName), "%s%d",I2C_DEVICE_ROOT, this->m_i2cBus);

    this->m_i2cHandler = open(deviceName, O_RDWR);
    if(this->m_i2cHandler < 0)
    {
        qDebug() << "pca9685Interface::i2cInit, error opening device: " << deviceName  << " errno: " << errno;
        return errno;
    }

    if(ioctl(this->m_i2cHandler, I2C_SLAVE, this->m_i2cAddr) < 0)
    {
        qDebug() << "pca9685Interface::i2cInit, error setting i2c address: " << this->m_i2cAddr << " errno: " << errno;
        return errno;
    }
#endif
    return 0;
}

void pca9685Interface::i2cByteWrite(quint8 reg, quint8 value)
{
#ifdef USE_I2C_BUS
    char buf[4];

    buf[0] = reg;
    buf[1] = value;
    buf[3] = 0;

    if (write(this->m_i2cHandler, buf, 2) != 2)
    {
        qDebug() << "pca9685Interface::i2cWrite, error i2c write reg: " << reg << " errno: " << errno;
    }
#endif
}

int pca9685Interface::pwmInit()
{
    this->i2cByteWrite(MODE1, 0x10);
    QThread::msleep(50);

    this->i2cByteWrite(PRE_SCALE, 0x10);    //TODO: Implement PWM frequency setup
    QThread::msleep(50);

    this->i2cByteWrite(MODE2, 0x00);    //TODO: Implement driver type setup
    QThread::msleep(50);

    this->i2cByteWrite(MODE1, 0x80);
    QThread::msleep(50);
}

void pca9685Interface::midi2pwm(struct midiMessage* message)
{
    quint8 chanOffset = 0;
    quint8 chanDutyH = 0;
    quint8 chanDutyL = 0;
    quint16 dutyW = 0;

    //TODO: Implement MIDI channel filter setup

    chanOffset = message->m_data1 - this->m_noteOffset;

    dutyW = (32 * message->m_data2);
    chanDutyL = (quint8)(dutyW & 0x00FF) ;
    chanDutyH = (quint8)(dutyW >> 8) & 0x0F;

    this->i2cByteWrite(LED0_ON_L + chanOffset, 0x00);
    this->i2cByteWrite(LED0_ON_H + chanOffset, 0x00);
    this->i2cByteWrite(LED0_OFF_L + chanOffset, chanDutyL);
    this->i2cByteWrite(LED0_OFF_H + chanOffset, chanDutyH);

}

void pca9685Interface::socketPoll()
{
    QByteArray data;
    QHostAddress sender;
    quint16 senderPort;
    qint64 pendingSize;

    struct midiMessage message;

    pendingSize = this->p_socket->pendingDatagramSize();
    if(pendingSize)
    {
        char* p = 0;
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
            qDebug() << this->midiMessageToStr(&message);
        }
    }
}

char* pca9685Interface::midiMessageToStr(struct midiMessage* message)
{
    static char dumpBuffer[1024];
    sprintf(dumpBuffer, "%s, channel=%02d, Data1=%03d, Data2=%03d",
            status2string[message->m_status],
            message->m_channel,
            message->m_data1,
            message->m_data2);

    return dumpBuffer;
}


