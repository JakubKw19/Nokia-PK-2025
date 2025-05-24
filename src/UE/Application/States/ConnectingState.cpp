#include "ConnectingState.hpp"
#include "NotConnectedState.hpp"
#include "ConnectedState.hpp"

namespace ue
{

ConnectingState::ConnectingState(Context &context)
    : BaseState(context, "ConnectingState")
{
    logger.logDebug("entry");
    context.user.showConnecting();
}

void ConnectingState::handleAttachAccept()
{
    context.timer.stopTimer();
    context.setState<ConnectedState>();
}

void ConnectingState::handleAttachReject()
{
    context.timer.stopTimer();
    context.setState<NotConnectedState>();
}

void ConnectingState::handleTimeout()
{
    context.setState<NotConnectedState>();
}

void ConnectingState::handleDisconnect()
{
    context.timer.stopTimer();
    context.setState<NotConnectedState>();
    context.logger.logInfo("Disconnected");
}
void ConnectingState::handleCallAccepted(common::PhoneNumber from)
{
    logger.logDebug("Ignored CallAccepted in ConnectingState from: ", from);
}

void ConnectingState::handleCallDropped(common::PhoneNumber from)
{
    logger.logDebug("Ignored CallDropped in ConnectingState from: ", from);
}

void ConnectingState::handleUnknownRecipient(common::PhoneNumber from)
{
    logger.logDebug("Ignored UnknownRecipient in ConnectingState from: ", from);
}

}
