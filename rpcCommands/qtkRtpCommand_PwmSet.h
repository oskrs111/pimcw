#ifndef QTKRTPCOMMAND_PWMSET__H
#define QTKRTPCOMMAND_PWMSET__H
#include <QObject>
#include <QEvent>
#include <QCoreApplication>
#include "qtkRtpCommand_id.h"
#include "qtkRtpCommand_.h"

//http://stackoverflow.com/questions/6061352/creating-a-custom-message-event-with-qt
const QEvent::Type PWM_EVENT = static_cast<QEvent::Type>(QEvent::User + k_rtp_command_id::rci_PwmSetCommand);

// Define your custom event subclass
class PwmEvent : public QEvent
{
    public:
        PwmEvent(const int channel, const int dutty):
            QEvent(PWM_EVENT),
            m_channel(channel),
            m_dutty(dutty)
        {
        }

        int getChannel() const
        {
            return m_channel;
        }

        int getDutty() const
        {
            return m_dutty;
        }

    private:
        int m_channel;
        int m_dutty;
};

class qtkRtpCommand_PwmSet : public qtkRtpCommand_
{
    Q_OBJECT
public:
    explicit qtkRtpCommand_PwmSet(QtkJsRpcServer *parent = 0);

private:
    void CommandInit();
    void CommandExecute(QJsonObject params);
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

inline void qtkRtpCommand_PwmSet::CommandExecute(QJsonObject params)
{
    int channel = 0;
    int dutty = 0;
    PwmEvent* event = 0;
    QObject* target = 0;
    QtkJsRpcServer* parent = 0;

	event = new PwmEvent(channel, dutty);
    parent = (QtkJsRpcServer*)this->parent();
    target = parent->getEventTarget("PWM_SERVICE");

    QCoreApplication::postEvent(target, event);
	
    QString result = QString("{'jsonrpc': '2.0', 'result': 'success', 'id': 1}");
    result = result.replace('\'', '"');
    emit commandDone(this->GetCommandId(), result.toLatin1());
}

#endif
