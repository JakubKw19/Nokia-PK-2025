#pragma once

#include "Logger/PrefixedLogger.hpp"
#include "Messages/PhoneNumber.hpp"
#include "IEventsHandler.hpp"
#include "Context.hpp"

namespace ue
{

using common::PhoneNumber;
using common::ILogger;

class Application : public IEventsHandler
{
public:
    Application(PhoneNumber phoneNumber,
                ILogger& iLogger,
                IBtsPort& bts,
                IUserPort& user,
                ITimerPort& timer);
    ~Application();

    // ITimerEventsHandler interface
    void handleTimeout() override;

    // IBtsEventsHandler interface
    void handleSib(common::BtsId btsId) override;
    void handleAttachAccept() override;
    void handleAttachReject() override;
    void handleComposeSms(common::PhoneNumber to, const std::string &text) override;
    const std::vector<Sms>& getAllSms() override;
    void handleViewSms(const std::string &index) override;
    void handleSmsReceived(common::PhoneNumber from, std::string text) override;
    void handleDisconnect() override;
    void handleSmsSend() override;
    void markSmsAsRead(size_t index) override;
private:
    Context context;
    common::PrefixedLogger logger;
    // SmsDb smsDb;

};

}
