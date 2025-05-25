#include "ConnectedState.hpp"
#include "ComposeSmsState.hpp"
#include "NotConnectedState.hpp"
#include "DialingState.hpp"
#include "RingingState.hpp"

namespace ue
{

ConnectedState::ConnectedState(Context &context)
    : BaseState(context, "ConnectedState")
{
    logger.logInfo("Connected");
    context.user.showConnected();
}

void ConnectedState::handleComposeSms(common::PhoneNumber to, const std::string &text) {
    context.setState<ComposeSmsState>(to, text);
}

void ConnectedState::handleDisconnect()
{
    context.setState<NotConnectedState>();
}

void ConnectedState::handleDial(common::PhoneNumber to)
{
    context.setState<DialingState>(to);
}
void ConnectedState::handleCallAccepted(common::PhoneNumber from)
{
    logger.logDebug("Ignored CallAccepted in ConnectedState from: ", from);
}

void ConnectedState::handleCallDropped(common::PhoneNumber from)
{
    logger.logDebug("Ignored CallDropped in ConnectedState from: ", from);
}

void ConnectedState::handleUnknownRecipient(common::PhoneNumber from)
{
    logger.logDebug("Ignored UnknownRecipient in ConnectedState from: ", from);
}
void ConnectedState::handleCallRequest(common::PhoneNumber from)
{
    logger.logInfo("Handling call request from: ", from);
    //userPort.showDialing(from);
    //btsPort.sendCallRequest(from);
    context.setState<RingingState>(from);
}


}
