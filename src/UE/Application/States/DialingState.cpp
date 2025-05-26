#include "DialingState.hpp"
#include "ConnectedState.hpp"
#include "TalkingState.hpp"

namespace ue
{

DialingState::DialingState(Context& context, common::PhoneNumber callee)
    : BaseState(context, "DialingState"), callee(callee)
{
    logger.logInfo("Dialing to: ", callee);
    context.bts.sendCallRequest(callee);
    context.user.showDialing(callee);
    context.timer.startTimer(std::chrono::seconds(60));
}

void DialingState::handleCallAccepted(common::PhoneNumber from)
{
    logger.logInfo("Call accepted by: ", from);
    context.timer.stopTimer();
    context.setState<TalkingState>(from);
}

void DialingState::handleCallDropped(common::PhoneNumber from)
{
    logger.logInfo("Call dropped by: ", from);
    context.timer.stopTimer();
    context.user.showMessage("Call was rejected");
    context.setState<ConnectedState>();
}

void DialingState::handleUnknownRecipient(common::PhoneNumber from)
{
    logger.logError("Peer unavailable: ", from);
    context.timer.stopTimer();
    context.user.showMessage("Peer not connected");
    context.setState<ConnectedState>();
}

void DialingState::handleTimeout()
{
    logger.logError("Dialing timeout");
    context.user.showMessage("Call timed out");
    context.setState<ConnectedState>();
}

void DialingState::handleUserReject()
{
    logger.logInfo("User cancelled call");
    context.user.clearCallMode();
    context.timer.stopTimer();
    context.bts.sendCallDropped(callee);
    context.setState<ConnectedState>();
}

void DialingState::handleUserHangUp() {
    logger.logInfo("User cancelled call before it was answered");
    context.timer.stopTimer();
    context.user.clearCallMode();
    context.bts.sendCallDropped(callee);
    context.setState<ConnectedState>();
}

}
