#ifndef QTKRTPCOMMAND_PCA9685SET__H
#define QTKRTPCOMMAND_PCA9685SET__H
#include <QObject>
#include <QCoreApplication>
#include "qtkRtpCommand_id.h"
#include "qtkRtpCommand_.h"
#include "pca9685interface.h"

//{"jsonrpc": "2.0", "method": "pca9685Set", "params": {"channel": 23, "dutty": 42}, "id": 4}
class qtkRtpCommand_pca9685Set : public qtkRtpCommand_
{
    Q_OBJECT
public:
    explicit qtkRtpCommand_pca9685Set(QtkJsRpcServer *parent = 0);

private:
    void CommandInit();
    void CommandExecute(QJsonObject params, int seqId);
};

inline qtkRtpCommand_pca9685Set::qtkRtpCommand_pca9685Set(QtkJsRpcServer *parent)
        : qtkRtpCommand_(parent)
{
	this->CommandInit();
}

inline void qtkRtpCommand_pca9685Set::CommandInit()
{
        this->SetCommandId(k_rtp_command_id::rci_pca9685SetCommand);
}

inline void qtkRtpCommand_pca9685Set::CommandExecute(QJsonObject params, int seqId)
{
    int channel = 0;
    int dutty = 0;    
    pca9685Interface* target = 0;
    QtkJsRpcServer* parent = 0;
    QString result;

	//OSLL: Here will arrive just the method params as JSON object. So parse it and execute.
    //      Just chek it has the correct parameters
    if(params.contains("channel") && params.contains("dutty"))
    {
		channel = params.take("channel").toInt();
		dutty = params.take("dutty").toInt();        
        parent = (QtkJsRpcServer*)this->parent();
        target = (pca9685Interface*)parent->getEventTarget("PCA9685_SERVICE");
        target->setChannelDutty(channel, dutty);
        result = QString("{\"jsonrpc\": \"2.0\", \"result\": \"success\", \"id\": %1}").arg(seqId,0,10);
    }
    else
    {
        result = QString("{\"jsonrpc\": \"2.0\", \"error\": {\"code\": -32602, \"message\": \"server error. invalid method parameters\"}, \"id\": %1}").arg(seqId,0,10);
    }

    emit commandDone(this->GetCommandId(), result.toLatin1());
}

#endif
