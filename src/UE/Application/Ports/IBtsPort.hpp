#pragma once

#include "Messages/BtsId.hpp"
#include "Messages/PhoneNumber.hpp"

namespace ue
{

class IBtsEventsHandler
{
public:
    virtual ~IBtsEventsHandler() = default;
    virtual void handleSmsReceived(common::PhoneNumber from, std::string text) = 0;
    virtual void handleSib(common::BtsId) = 0;
    virtual void handleAttachAccept() = 0;
    virtual void handleAttachReject() = 0;
    virtual void handleDisconnect() = 0;
    virtual void handleCallAccepted(common::PhoneNumber from) = 0;
    virtual void handleCallDropped(common::PhoneNumber from) = 0;
    virtual void handleUnknownRecipient(common::PhoneNumber from) = 0;
    virtual void handleCallRequest(common::PhoneNumber from) = 0;
    virtual void handleUserAccept() = 0;
    virtual void handleUserReject() = 0;
    virtual void handleUserHangUp() = 0;
    virtual void handleReceiveCallTalk(common::PhoneNumber from, const std::string &text) = 0;
};

class IBtsPort
{
public:
    virtual ~IBtsPort() = default;
    virtual void sendAttachRequest(common::BtsId) = 0;
    virtual void sendSms(common::PhoneNumber to, const std::string &text) = 0;
    virtual void sendCallRequest(common::PhoneNumber to) = 0;
    virtual void sendCallDropped(common::PhoneNumber to) = 0;
    virtual void sendCallAccepted(common::PhoneNumber to) = 0;
    virtual void showCallRequest(common::PhoneNumber from) = 0;
    virtual void showTalking(common::PhoneNumber interlocutor) = 0;
    virtual void sendCallTalk(common::PhoneNumber to, const std::string &text) = 0;
};

}
