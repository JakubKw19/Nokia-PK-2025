#include "TalkingState.hpp"
#include "ConnectedState.hpp"
#include "UeGui/ICallMode.hpp"

namespace ue
{

    TalkingState::TalkingState(Context& context, common::PhoneNumber interlocutor)
        : BaseState(context, "TalkingState"), interlocutor(interlocutor)
    {
        logger.logInfo("Talking with: ", interlocutor);
        context.user.showTalking(interlocutor);
        // Timer dla maksymalnego czasu rozmowy
        // context.timer.startTimer(std::chrono::minutes(60));
    }

    void TalkingState::handleUserHangUp()
    {
        logger.logInfo("User ended call with: ", interlocutor);
        context.user.clearCallMode();
        context.bts.sendCallDropped(interlocutor);
        context.setState<ConnectedState>();
    }

    void TalkingState::handleCallAccepted(common::PhoneNumber from)
    {
        logger.logError("Unexpected CallAccepted from: ", from);
    }

    void TalkingState::handleCallDropped(common::PhoneNumber from)
    {
        context.user.clearCallMode();
        if (from == interlocutor)
        {
            logger.logInfo("Call dropped by interlocutor: ", from);
            
            context.user.showMessage("Call ended by interlocutor");
            context.setState<ConnectedState>();
        }
        else
        {
            logger.logError("Unexpected CallDropped from: ", from);
        }
    }

    void TalkingState::handleMessageSend(common::PhoneNumber to, const std::string &text)
    {
        logger.logInfo("Sending message to: ", to, ", text: ", text);
        context.bts.sendCallTalk(to, text);
    }



    void TalkingState::handleUnknownRecipient(common::PhoneNumber from)
    {
        logger.logError("Unexpected UnknownRecipient from: ", from);
    }

    void TalkingState::handleCallRequest(common::PhoneNumber from)
    {
        logger.logInfo("Rejected call request from: ", from, " (already talking)");
        context.bts.sendCallDropped(from);
    }

    void TalkingState::handleTimeout()
    {
        logger.logInfo("Call time limit reached");
        context.user.showMessage("Call time limit reached");
        context.bts.sendCallDropped(interlocutor);
        context.setState<ConnectedState>();
    }

    void TalkingState::handleReceiveCallTalk(common::PhoneNumber from, const std::string &text)
    {
        if (from == interlocutor)
        {
            logger.logInfo("Received message from: ", from, ", text: ", text);
            context.user.addMessageFromCall(from, text);
        }
        else
        {
            logger.logError("Received message from unknown number: ", from);
        }
    }

}