#ifndef QTKRTPCOMMAND_SHELLRUN__H
#define QTKRTPCOMMAND_SHELLRUN__H
#include <QObject>
#include <QProcess>
#include "qtkRtpCommand_id.h"
#include "qtkRtpCommand_.h"

//{"jsonrpc": "2.0", "method": "shellRun", "params": {"command": "run.sh", "timeout":5000}, "id": 4}
class qtkRtpCommand_ShellRun : public qtkRtpCommand_
{
    Q_OBJECT
public:
    explicit qtkRtpCommand_ShellRun(QtkJsRpcServer *parent = 0);

private:
    void CommandInit();
    void CommandExecute(QJsonObject params, int seqId);
};

inline qtkRtpCommand_ShellRun::qtkRtpCommand_ShellRun(QtkJsRpcServer *parent)
        : qtkRtpCommand_(parent)
{
	this->CommandInit();
}

inline void qtkRtpCommand_ShellRun::CommandInit()
{
        this->SetCommandId(k_rtp_command_id::rci_ShellRunCommand);
}

inline void qtkRtpCommand_ShellRun::CommandExecute(QJsonObject params, int seqId)
{             
    QString result;
	QString command;
    QProcess proc;
    int timeout = 30000;

	//OSLL: Here will arrive just the method params as JSON object. So parse it and execute.
    //      Just chek it has the correct parameters
    if(params.contains("command"))
    {
		command = params.take("command").toString();	
        timeout = params.take("timeout").toInt();

        proc.start(command);

        if(proc.waitForFinished(timeout) == true)
		{			
            QString output(proc.readAllStandardOutput());
            if(output.length() == 0) output = QString("null");
            result = QString("{\"jsonrpc\": \"2.0\", \"result\": \"success\", \"stdout\":\"%2\" \"id\": %1}").arg(seqId,0,10).arg(output);
		}
		else
		{
			result = QString("{\"jsonrpc\": \"2.0\", \"result\": \"fail\", \"id\": %1}").arg(seqId,0,10);
		}
			
    }
    else
    {
        result = QString("{\"jsonrpc\": \"2.0\", \"error\": {\"code\": -32602, \"message\": \"server error. invalid method parameters\"}, \"id\": %1}").arg(seqId,0,10);
    }

    emit commandDone(this->GetCommandId(), result.toLatin1());
}

#endif
