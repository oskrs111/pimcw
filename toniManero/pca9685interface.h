#ifndef PCA9685INTERFACE_H
#define PCA9685INTERFACE_H
#include <QObject>
#include <QUdpSocket>
#include "../qtkVirtualMIDI/qtkvirtualmidistructs.h"

#define I2C_DEVICE_ROOT  "/dev/i2c-"

#define PRE_SCALE   0xFE
#define MODE1       0x00
#define MODE2       0x01
#define LED0_ON_L   0x06
#define LED0_ON_H   0x07
#define LED0_OFF_L  0x08
#define LED0_OFF_H  0x09

#define LED_ALL_ON_L  0xFA
#define LED_ALL_ON_H  0xFB
#define LED_ALL_OFF_L  0xFC
#define LED_ALL_OFF_H  0xFD
#define MAX_CHANNELS 16

class pca9685Interface : public QObject
{
    Q_OBJECT
public:
    explicit pca9685Interface(quint16 udpPort, quint8 i2cBus, quint8 i2cAddr, quint8 noteOffset, QObject *parent = 0);
    ~pca9685Interface();     
     void setChannelDutty(quint8 channel, quint8 dutty);
     quint8 getChannelDutty(quint8 channel);
     quint8* getAllChannelDutty(quint8* channelCount);

private:
    void networkInit();
    void socketPoll();
    int i2cInit();
    int pwmInit();

    void i2cByteWrite(quint8 reg, quint8 value);
    void midi2pwm(struct midiMessage* message);
    void event2pwm(unsigned char channel, unsigned char dutty);

    bool event(QEvent *event);

    char* midiMessageToStr(struct midiMessage* message);
    quint16 m_udpPort;
    quint8 m_i2cBus;
    quint8 m_i2cAddr;
    quint8 m_noteOffset;
    quint8 a_duttyValues[MAX_CHANNELS];
    int m_i2cHandler;
    QUdpSocket* p_socket;

#ifdef USE_I2C_BUS


#endif

signals:

public slots:    
    void OnReadyRead();
};

#endif // PCA9685INTERFACE_H
