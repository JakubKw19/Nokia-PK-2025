#include "NotConnectedState.hpp"
#include "ConnectingState.hpp"

namespace ue
{

NotConnectedState::NotConnectedState(Context &context)
    : BaseState(context, "NotConnectedState")
{
    logger.logInfo("Not Connected");
    context.user.showNotConnected();
}

void NotConnectedState::handleSib(common::BtsId btsId)
{
    using namespace std::chrono_literals;
    context.bts.sendAttachRequest(btsId);
    context.setState<ConnectingState>();
    context.timer.startTimer(500ms);
}

void NotConnectedState::handleCallAccepted(common::PhoneNumber from)
{
    logger.logDebug("Ignored CallAccepted from ", from, " in NotConnectedState");
}

void NotConnectedState::handleCallDropped(common::PhoneNumber from)
{
    logger.logDebug("Ignored CallDropped from ", from, " in NotConnectedState");
}

void NotConnectedState::handleUnknownRecipient(common::PhoneNumber from)
{
    logger.logDebug("Ignored UnknownRecipient from ", from, " in NotConnectedState");
}


}
