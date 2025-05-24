#include "ComposeSmsState.hpp"
#include <IUeGui.hpp>
#include <UeGui/ISmsComposeMode.hpp>
// #include <IUserPort.hpp>

namespace ue
{

    ComposeSmsState::ComposeSmsState(Context &context, common::PhoneNumber to, const std::string &text)
    : BaseState(context, "ConnectedState")
{
    this->to = to;
    this->message = text;
    // logger.logInfo("Compose SMS to: " + common::to_string(to) + ", text: " + text);
}

    void ComposeSmsState::handleComposeSms(common::PhoneNumber to, const std::string &text)
    {
        logger.logInfo("Compose SMS to: " + common::to_string(to) + ", text: " + text);
        context.bts.sendSms(to, message);
    }
    void ComposeSmsState::handleCallAccepted(common::PhoneNumber from)
    {
        logger.logDebug("Ignored CallAccepted in ComposeSmsState");
    }

    void ComposeSmsState::handleCallDropped(common::PhoneNumber from)
    {
        logger.logDebug("Ignored CallDropped in ComposeSmsState");
    }

    void ComposeSmsState::handleUnknownRecipient(common::PhoneNumber from)
    {
        logger.logDebug("Ignored UnknownRecipient in ComposeSmsState");
    }


}
