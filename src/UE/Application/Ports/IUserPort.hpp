#pragma once
#include "Messages/PhoneNumber.hpp"
#include "IUeGui.hpp"
#include "Smsdb.hpp"


namespace ue
{

class IUserEventsHandler
{
public:
    virtual ~IUserEventsHandler() = default;
    virtual void handleComposeSms(common::PhoneNumber to, const std::string &text) = 0;
    virtual void handleViewSms(const std::string &index) = 0;
    virtual const std::vector<Sms>& getAllSms() = 0;
    virtual void handleSmsSend() = 0;
    virtual void markSmsAsRead(size_t index) = 0;
    virtual void handleDial(common::PhoneNumber to) = 0;
    virtual void handleUserAccept() = 0;
    virtual void handleUserReject() = 0;
    virtual void handleUserHangUp() = 0;
    virtual void handleMessageSend(common::PhoneNumber to, const std::string &text) = 0;
};

class IUserPort
{
public:
    virtual ~IUserPort() = default;
    virtual void showNotConnected() = 0;
    virtual void showConnecting() = 0;
    virtual void showConnected() = 0;
    virtual void showSmsList(const std::vector<Sms>& messages) = 0;
    virtual void showDialing(common::PhoneNumber to) = 0;
    virtual void showMessage(const std::string& text) = 0;
    virtual void showCallRequest(common::PhoneNumber from) = 0;
    virtual void showTalking(common::PhoneNumber interlocutor) = 0;
    virtual void addMessageFromCall(common::PhoneNumber from, const std::string& text) = 0;
    virtual void clearCallMode() = 0;
    // virtual common::PhoneNumber getRecipientPhoneNumber() const = 0;
    // virtual std::string getSmsText() const = 0;
};

}
