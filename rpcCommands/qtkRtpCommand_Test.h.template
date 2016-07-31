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
    void CommandExecute(QJsonObject params);
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

inline void qtkRtpCommand_Test::CommandExecute(QJsonObject params)
{
    int sum = 69;
    QString result = QString("{'jsonrpc': '2.0', 'result': %1, 'id': 1}").arg(sum,0,10);
    result = result.replace('\'', '"');
    emit commandDone(this->GetCommandId(), result.toLatin1());
}

#endif
