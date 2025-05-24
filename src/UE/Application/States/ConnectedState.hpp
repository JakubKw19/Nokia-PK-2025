#pragma once

#include "BaseState.hpp"

namespace ue
{

class ConnectedState : public BaseState
{
public:
    ConnectedState(Context& context);
    void handleComposeSms(common::PhoneNumber to, const std::string &text);
    void handleDisconnect() override;
    void handleDial(common::PhoneNumber to);
    void handleCallAccepted(common::PhoneNumber from) override;
    void handleCallDropped(common::PhoneNumber from) override;
    void handleUnknownRecipient(common::PhoneNumber from) override;
    void handleCallRequest(common::PhoneNumber) override;

};

}
