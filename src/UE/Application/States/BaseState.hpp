#pragma once

#include "IEventsHandler.hpp"
#include "Logger/PrefixedLogger.hpp"
#include "Context.hpp"

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
        logger.logInfo("baseState: ");
    };
    void handleViewSms(const std::string &index) override {
        logger.logInfo("baseState: ");
    };
    void handleSmsReceived(common::PhoneNumber from, std::string text) override {
        logger.logInfo("baseState: received SMS from: ", from);
    };
    void handleDisconnect() override;

protected:
    Context& context;
    common::PrefixedLogger logger;
};

}
