#ifndef QTKRTPCOMMAND_PWMSET__H
#define QTKRTPCOMMAND_PWMSET__H
#include <QObject>
#include <QCoreApplication>
#include "qtkRtpCommand_id.h"
#include "qtkRtpCommand_.h"
#include "pca9685events.h"

class qtkRtpCommand_PwmSet : public qtkRtpCommand_
{
    Q_OBJECT
public:
    explicit qtkRtpCommand_PwmSet(QtkJsRpcServer *parent = 0);

private:
    void CommandInit();
    void CommandExecute(QJsonObject params, int seqId);
};

inline qtkRtpCommand_PwmSet::qtkRtpCommand_PwmSet(QtkJsRpcServer *parent)
        : qtkRtpCommand_(parent)
{
	this->CommandInit();
}

inline void qtkRtpCommand_PwmSet::CommandInit()
{
        this->SetCommandId(k_rtp_command_id::rci_PwmSetCommand);
}

inline void qtkRtpCommand_PwmSet::CommandExecute(QJsonObject params, int seqId)
{
    int channel = 0;
    int dutty = 0;
    PwmEvent* event = 0;
    QObject* target = 0;
    QtkJsRpcServer* parent = 0;
    QString result;

	//OSLL: Here will arrive just the method params as JSON object. So parse it and execute.
    //      Just chek it has the correct parameters
    if(params.contains("channel") && params.contains("dutty"))
    {
		channel = params.take("channel").toInt();
		dutty = params.take("dutty").toInt();
        event = new PwmEvent(channel, dutty);
        parent = (QtkJsRpcServer*)this->parent();
        target = parent->getEventTarget("PWM_SERVICE");
        QCoreApplication::postEvent(target, event);
        result = QString("{\"jsonrpc\": \"2.0\", \"result\": \"success\", \"id\": %1}").arg(seqId,0,10);
    }
    else
    {
        result = QString("{\"jsonrpc\": \"2.0\", \"error\": {\"code\": -32602, \"message\": \"server error. invalid method parameters\"}, \"id\": %1}").arg(seqId,0,10);
    }

    emit commandDone(this->GetCommandId(), result.toLatin1());
}

#endif
