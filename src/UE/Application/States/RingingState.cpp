#include "RingingState.hpp"
#include "ConnectedState.hpp"
#include "TalkingState.hpp"

namespace ue
{
    class TalkingState;

    RingingState::RingingState(Context& context, common::PhoneNumber caller)
        : BaseState(context, "RingingState"), caller(caller)
    {
        logger.logInfo("Incoming call from: ", caller);
        context.user.showCallRequest(caller);
        context.timer.startTimer(std::chrono::seconds(60));
    }

    void RingingState::handleUserAccept()
    {
        logger.logInfo("User accepted call from: ", caller);
        context.timer.stopTimer();
        context.bts.sendCallAccepted(caller);
        context.setState<TalkingState>(caller);
    }

    void RingingState::handleUserReject()
    {
        logger.logInfo("User rejected call from: ", caller);
        context.user.clearCallMode();
        context.timer.stopTimer();
        context.bts.sendCallDropped(caller);
        context.setState<ConnectedState>();
    }

    void RingingState::handleCallAccepted(common::PhoneNumber from)
    {
        logger.logError("Unexpected CallAccepted from: ", from);
    }

    void RingingState::handleCallDropped(common::PhoneNumber from)
    {
        if (from == caller)
        {
            logger.logInfo("Call dropped by caller: ", from);
            context.timer.stopTimer();
            context.user.showMessage("Caller cancelled the call");
            context.setState<ConnectedState>();
        }
        else
        {
            logger.logError("Unexpected CallDropped from: ", from);
        }
    }

    void RingingState::handleUnknownRecipient(common::PhoneNumber from)
    {
        logger.logError("Unexpected UnknownRecipient from: ", from);
    }

    void RingingState::handleTimeout()
    {
        logger.logInfo("Call request timeout");
        context.user.showMessage("Call request expired");
        context.setState<ConnectedState>();
    }

}