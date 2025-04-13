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

}
