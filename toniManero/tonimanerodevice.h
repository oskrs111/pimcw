#ifndef TONIMANERODEVICE_H
#define TONIMANERODEVICE_H

#include <QObject>

class toniManeroDevice : public QObject
{
    Q_OBJECT
public:
    explicit toniManeroDevice(QObject *parent = 0);
    virtual void writeChannelValue(quint16 channel, quint8 value);
    virtual quint8 readChannelValue(quint16 channel);

signals:

public slots:
};

#endif // TONIMANERODEVICE_H
