#pragma once

#include "BaseState.hpp"

namespace ue
{

class ConnectingState : public BaseState
{
public:
    ConnectingState(Context& context);
    void handleAttachAccept() override;
    void handleAttachReject() override;
    void handleTimeout() override;
    void handleDisconnect() override;
    void handleCallAccepted(common::PhoneNumber from) override;
    void handleCallDropped(common::PhoneNumber from) override;
    void handleUnknownRecipient(common::PhoneNumber from) override;
};

}
