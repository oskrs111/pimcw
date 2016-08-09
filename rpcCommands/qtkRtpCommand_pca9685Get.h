#ifndef QTKRTPCOMMAND_PCA9685GET__H
#define QTKRTPCOMMAND_PCA9685GET__H
#include <QObject>
#include <QCoreApplication>
#include "qtkRtpCommand_id.h"
#include "qtkRtpCommand_.h"
#include "pca9685interface.h"

class qtkRtpCommand_pca9685Get : public qtkRtpCommand_
{
    Q_OBJECT
public:
    explicit qtkRtpCommand_pca9685Get(QtkJsRpcServer *parent = 0);

private:
    void CommandInit();
    void CommandExecute(QJsonObject params, int seqId);
};

inline qtkRtpCommand_pca9685Get::qtkRtpCommand_pca9685Get(QtkJsRpcServer *parent)
        : qtkRtpCommand_(parent)
{
	this->CommandInit();
}

inline void qtkRtpCommand_pca9685Get::CommandInit()
{
        this->SetCommandId(k_rtp_command_id::rci_pca9685GetCommand);
}

inline void qtkRtpCommand_pca9685Get::CommandExecute(QJsonObject params, int seqId)
{
    int channel = 0;
    int dutty = 0;    
    pca9685Interface* target = 0;
    QtkJsRpcServer* parent = 0;
    QString result;

	//OSLL: Here will arrive just the method params as JSON object. So parse it and execute.
    //      Just chek it has the correct parameters
    if(params.contains("channel"))
    {
		channel = params.take("channel").toInt();
		dutty = params.take("dutty").toInt();        
        parent = (QtkJsRpcServer*)this->parent();
        target = (pca9685Interface*)parent->getEventTarget("PCA9685_SERVICE");
        dutty = target->getChannelDutty(channel);
        result = QString("{\"jsonrpc\": \"2.0\", \"result\":{\"channel\": %2, \"dutty\": %3},\"id\": %1}").arg(seqId,0,10).arg(channel,0,10).arg(dutty,0,10);
    }
    else
    {
        result = QString("{\"jsonrpc\": \"2.0\", \"error\": {\"code\": -32602, \"message\": \"	Invalid params. Invalid method parameter(s)\"}, \"id\": %1}").arg(seqId,0,10);
    }

    emit commandDone(this->GetCommandId(), result.toLatin1());
}

#endif
