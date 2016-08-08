#ifndef PCA9685EVENTS_H
#define PCA9685EVENTS_H
#include <QEvent>
#include "qtkRtpCommand_id.h"
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
#endif
