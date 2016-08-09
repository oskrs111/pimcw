#ifndef QTKRTPCOMMAND_pca9685GETALL__H
#define QTKRTPCOMMAND_PCA9685GETALL__H
#include <QObject>
#include <QCoreApplication>
#include "qtkRtpCommand_id.h"
#include "qtkRtpCommand_.h"
#include "pca9685interface.h"

class qtkRtpCommand_pca9685GetAll : public qtkRtpCommand_
{
    Q_OBJECT
public:
    explicit qtkRtpCommand_pca9685GetAll(QtkJsRpcServer *parent = 0);

private:
    void CommandInit();
    void CommandExecute(QJsonObject params, int seqId);
};

inline qtkRtpCommand_pca9685GetAll::qtkRtpCommand_pca9685GetAll(QtkJsRpcServer *parent)
        : qtkRtpCommand_(parent)
{
	this->CommandInit();
}

inline void qtkRtpCommand_pca9685GetAll::CommandInit()
{
        this->SetCommandId(k_rtp_command_id::rci_pca9685GetAllCommand);
}

inline void qtkRtpCommand_pca9685GetAll::CommandExecute(QJsonObject params, int seqId)
{
    int channel = 0;
    quint8* dutty = 0;
    quint8 length = 0;
    pca9685Interface* target = 0;
    QtkJsRpcServer* parent = 0;
    QString result;
    QString duttyArray;

    channel = params.take("channel").toInt();
    parent = (QtkJsRpcServer*)this->parent();
    target = (pca9685Interface*)parent->getEventTarget("PCA9685_SERVICE");
    dutty = target->getAllChannelDutty(&length);
    for(int t = 0; t < length; t++)
    {
        duttyArray.append(QString("%1").arg(dutty[t],0,10));
        if(t < (length-1)) duttyArray.append(",");
    }

    result = QString("{\"jsonrpc\": \"2.0\", \"result\":{\"channelCount\": %2, \"duttyArray\": [%3]},\"id\": %1}").arg(seqId,0,10).arg(length,0,10).arg(duttyArray);
    emit commandDone(this->GetCommandId(), result.toLatin1());
}

#endif
