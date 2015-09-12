#ifndef QTKRTPCOMMAND_TEST__H
#define QTKRTPCOMMAND_TEST__H
#include <QObject>
#include "qtkRtpCommand_id.h"
#include "qtkRtpCommand_.h"

//This is a example template. Place this file and other qtkRtpCommand_xxxxx.h outside this folder ;-)...

class qtkRtpCommand_Test : public qtkRtpCommand_
{
    Q_OBJECT
public:
    explicit qtkRtpCommand_Test(QtkJsRpcServer *parent = 0);

private:
    void CommandInit();
    void CommandExecute(QJsonObject params, int seqId);
};

inline qtkRtpCommand_Test::qtkRtpCommand_Test(QtkJsRpcServer *parent)
        : qtkRtpCommand_(parent)
{
	this->CommandInit();
}

inline void qtkRtpCommand_Test::CommandInit()
{
    this->SetCommandId(k_rtp_command_id::rci_TestCommand);
}

inline void qtkRtpCommand_Test::CommandExecute(QJsonObject params, int seqId)
{    
    QString result = QString("{\"jsonrpc\": \"2.0\", \"result\": \"success\", \"id\": %1}").arg(seqId,0,10);
    emit commandDone(this->GetCommandId(), result.toLatin1());
}

#endif
