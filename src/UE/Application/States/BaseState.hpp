#pragma once

#include "IEventsHandler.hpp"
#include "Logger/PrefixedLogger.hpp"
#include "Context.hpp"
#include "Smsdb.hpp"

namespace ue
{

class BaseState : public IEventsHandler
{
public:
    BaseState(Context& context, const std::string& name);
    ~BaseState() override;

    // ITimerEventsHandler interface
    void handleTimeout() override;

    // IBtsEventsHandler interface
    void handleSib(common::BtsId btsId) override;
    void handleAttachAccept() override;
    void handleAttachReject() override;
    void handleComposeSms(common::PhoneNumber to, const std::string &text) override {
        logger.logInfo("baseState: handleComposeSms");
    };
    void handleSmsSend() override {
        logger.logInfo("BaseState: handleSmsSend called (default)");
    }
    void handleViewSms(const std::string &index) override {
        logger.logInfo("baseState: ");
    };
    void handleSmsReceived(common::PhoneNumber from, std::string text) override {
        logger.logInfo("baseState: received SMS from: ", from);
    };
    void markSmsAsRead(size_t index) override {
        logger.logInfo("baseState: markSmsAsRead called for index: ", index);
        context.smsDb.markAsRead(index);
    };
    const std::vector<Sms>& getAllSms() override {
        logger.logInfo("baseState: ");
        return context.smsDb.getAllSms();
    };
    void handleDisconnect() override;

protected:
    Context& context;
    common::PrefixedLogger logger;
};

}
