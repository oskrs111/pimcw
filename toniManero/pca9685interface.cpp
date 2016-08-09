#include <QDebug>
#include <QThread>
#include "pca9685interface.h"
#include "pca9685events.h"


#ifdef USE_I2C_BUS
extern "C"
{
#ifdef USE_LINUX_PLATFORM
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#endif
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>
}
#endif

//#define PCA9685_INTERFACE_SERVICE_NAME "PWM_SERVICE"
#define PCA9685_INTERFACE_SERVICE_NAME "PCA9685_SERVICE"

pca9685Interface::pca9685Interface(quint16 udpPort, quint8 i2cBus, quint8 i2cAddr, quint8 noteOffset, QObject *parent) : QObject(parent)
{
    this->m_udpPort = udpPort;
    this->m_i2cBus = i2cBus;
    this->m_i2cAddr = i2cAddr;
    this->m_noteOffset = noteOffset;
    this->m_i2cHandler = 0;
    memset(&this->a_duttyValues[0], 0x00, sizeof(this->a_duttyValues));

    this->setObjectName(QString(PCA9685_INTERFACE_SERVICE_NAME));

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
    connect(this->p_socket,SIGNAL(readyRead()),this,SLOT(OnReadyRead()));
    qDebug() << "[pca9685Interface] listening on udp port: " << this->m_udpPort;
}

int pca9685Interface::i2cInit()
{
#ifdef USE_I2C_BUS
    char deviceName[32];

    snprintf(deviceName, sizeof(deviceName), "%s%d",I2C_DEVICE_ROOT, this->m_i2cBus);

    this->m_i2cHandler = open(deviceName, O_RDWR | O_NONBLOCK);
    if(this->m_i2cHandler < 0)
    {
        qDebug() << "[pca9685Interface] i2cInit, error opening device: " << deviceName  << " errno: " << errno;
        return errno;
    }

    if(ioctl(this->m_i2cHandler, I2C_SLAVE, this->m_i2cAddr) < 0)
    {
        qDebug() << "[pca9685Interface] i2cInit, error setting i2c address: " << this->m_i2cAddr << " errno: " << errno;
        return errno;
    }

    qDebug() << "[pca9685Interface] i2cInit succesfull for device address: " << this->m_i2cAddr;

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
        qDebug() << "[pca9685Interface] i2cWrite, error i2c write reg: " << reg << " errno: " << errno;
    }
    else
    {
        //qDebug() << "pca9685Interface::i2cWrite, reg: " << reg << " value: " << value;
    }
#endif
}

int pca9685Interface::pwmInit()
{
    this->i2cByteWrite(MODE1, 0x10);
    QThread::msleep(50);

    this->i2cByteWrite(PRE_SCALE, 0x10);    //TODO: Implement PWM frequency setup
    QThread::msleep(50);

    this->i2cByteWrite(MODE2, 0x10);    //TODO: Implement driver type setup
    QThread::msleep(50);

    this->i2cByteWrite(MODE1, 0x80);
    QThread::msleep(50);

    this->i2cByteWrite(LED_ALL_ON_L, 0x00);
    this->i2cByteWrite(LED_ALL_ON_H, 0x00);
    this->i2cByteWrite(LED_ALL_OFF_L, 0xFF);
    this->i2cByteWrite(LED_ALL_OFF_H, 0x0F);
    QThread::msleep(250);

    this->i2cByteWrite(LED_ALL_ON_L, 0x00);
    this->i2cByteWrite(LED_ALL_ON_H, 0x00);
    this->i2cByteWrite(LED_ALL_OFF_L, 0x00);
    this->i2cByteWrite(LED_ALL_OFF_H, 0x00);

    return 0;

    /*
     * raspi i2c setup:
    sudo nano /etc/modprobe.d/i2c.conf
    options i2c_bcm2708 baudrate=400000
    */

}

void pca9685Interface::midi2pwm(struct midiMessage* message)
{
    quint8 chanOffset = 0;
    quint8 chanDutyH = 0;
    quint8 chanDutyL = 0;
    quint16 dutyW = 0;

    //TODO: Implement MIDI channel filter setup

    if(this->m_noteOffset > message->m_data1) this->m_noteOffset = 0;
    chanOffset = (message->m_data1 - this->m_noteOffset) * 4;

    dutyW = (32 * message->m_data2);
    chanDutyL = (quint8)(dutyW & 0x00FF) ;
    chanDutyH = (quint8)(dutyW >> 8) & 0x0F;

    //this->i2cByteWrite(LED0_ON_L + chanOffset, 0x00);
    //this->i2cByteWrite(LED0_ON_H + chanOffset, 0x00);
    this->i2cByteWrite(LED0_OFF_L + chanOffset, chanDutyL);
    this->i2cByteWrite(LED0_OFF_H + chanOffset, chanDutyH);

}

void pca9685Interface::event2pwm(unsigned char channel, unsigned char dutty)
{
    quint8 chanDutyH = 0;
    quint8 chanDutyL = 0;
    quint16 dutyW = 0;
  
	if(dutty > 100) dutty = 100; //OSLL: Here are working with 0% to 100% range!


    dutyW = (40 * dutty);
    chanDutyL = (quint8)(dutyW & 0x00FF) ;
    chanDutyH = (quint8)(dutyW >> 8) & 0x0F;

    //this->i2cByteWrite(LED0_ON_L + chanOffset, 0x00);
    //this->i2cByteWrite(LED0_ON_H + chanOffset, 0x00);
    this->i2cByteWrite(LED0_OFF_L + (channel * 4), chanDutyL);
    this->i2cByteWrite(LED0_OFF_H + (channel * 4), chanDutyH);

}

void pca9685Interface::setChannelDutty(quint8 channel, quint8 dutty)
{
    if(channel >= MAX_CHANNELS) return; //Error.
    this->event2pwm(channel, dutty);
    this->a_duttyValues[channel] = dutty;
}

quint8 pca9685Interface::getChannelDutty(quint8 channel)
{
    if(channel >= MAX_CHANNELS) return 0xFF; //Error.
    return this->a_duttyValues[channel];

}

quint8* pca9685Interface::getAllChannelDutty(quint8* channelCount)
{
    *channelCount = sizeof(this->a_duttyValues);
    return &this->a_duttyValues[0];
}

void pca9685Interface::socketPoll()
{
    static quint8 index = 128; //Do not init to 0x00!!!
    QByteArray data;
    QHostAddress sender;
    quint16 senderPort;
    qint64 pendingSize;

    struct midiMessage message;

    pendingSize = this->p_socket->pendingDatagramSize();
    if(pendingSize > sizeof(struct midiMessage)) qDebug() << "*" << pendingSize;
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

            if(((message.m_status == MM_NOTE_ON) || (message.m_status == MM_NOTE_OFF)) && (index != message.m_index))
            {
                this->midi2pwm(&message);
                index = message.m_index;
                qDebug() << this->midiMessageToStr(&message);
            }            
        }
    }
}

void pca9685Interface::OnReadyRead()
{
    this->socketPoll();
}

char* pca9685Interface::midiMessageToStr(struct midiMessage* message)
{
    static long int last_time = 0;
    static long int time_difference = 0;
#ifdef USE_LINUX_PLATFORM
    static struct timespec gettime_now;
    clock_gettime(CLOCK_REALTIME, &gettime_now);
    time_difference = (abs(gettime_now.tv_nsec - last_time) / 1000);
    last_time = gettime_now.tv_nsec;
#endif
    static char dumpBuffer[1024];            

    sprintf(dumpBuffer, "%s, Ch=%02d, D1=%03d, D2=%03d, delay=%d us",
            status2string[message->m_status],
            message->m_channel,
            message->m_data1,
            message->m_data2,
            time_difference);


    //sprintf(dumpBuffer, "delay=%d us",time_difference);

    return dumpBuffer;
}

bool pca9685Interface::event(QEvent *event)
{
    if (event->type() == PWM_EVENT)
    {
        PwmEvent *myEvent = static_cast<PwmEvent *>(event);
        this->pca9685Interface::event2pwm((unsigned char)myEvent->getChannel(), (unsigned char)myEvent->getDutty());
		qDebug() << "[pca9685Interface] PwmEvent, Channel: " << myEvent->getChannel() << " Dutty: " << myEvent->getDutty();		
        return true;
    }
    return QObject::event(event);
}
