#include "ComposeSmsState.hpp"
#include "ConnectedState.hpp"
#include <IUeGui.hpp>
#include <UeGui/ISmsComposeMode.hpp>
// #include <IUserPort.hpp>

namespace ue
{

    ComposeSmsState::ComposeSmsState(Context &context, common::PhoneNumber to, const std::string &text)
    : BaseState(context, "ComposeSmsState"),
      to(to),
      message(text)
{
    this->handleComposeSms(to, text);
}

    void ComposeSmsState::handleComposeSms(common::PhoneNumber to, const std::string &text)
    {
        logger.logInfo("ComposeSmsState: handleComposeSms called");
        context.bts.sendSms(to, message);

    }

    void ComposeSmsState::handleSmsSend()
    {
        logger.logInfo("ComposeSmsState: Sending SMS to: " + common::to_string(to));
        context.bts.sendSms(to, message);
        context.setState<ConnectedState>();
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
