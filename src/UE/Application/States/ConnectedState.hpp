#pragma once

#include "BaseState.hpp"

namespace ue
{

class ConnectedState : public BaseState
{
public:
    ConnectedState(Context& context);
    void handleComposeSms(common::PhoneNumber to, const std::string &text);
    void handleViewSms(const std::string &index) override;
    void handleSmsReceived(common::PhoneNumber from, std::string text) override;
    const std::vector<Sms>& getAllSms() override;
    void handleDisconnect() override;
    void markSmsAsRead(size_t index) override;
    void handleDial(common::PhoneNumber to) override;
    void handleCallAccepted(common::PhoneNumber from) override;
    void handleCallDropped(common::PhoneNumber from) override;
    void handleUnknownRecipient(common::PhoneNumber from) override;
    void handleCallRequest(common::PhoneNumber) override;
};

}
