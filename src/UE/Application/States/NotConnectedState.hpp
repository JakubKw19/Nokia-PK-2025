#pragma once

#include "BaseState.hpp"
#include "Messages/PhoneNumber.hpp"

namespace ue
{

class NotConnectedState : public BaseState
{
public:
    NotConnectedState(Context& context);
    void handleSib(common::BtsId btsId);
    void handleCallAccepted(common::PhoneNumber from) override;
    void handleCallDropped(common::PhoneNumber from) override;
    void handleUnknownRecipient(common::PhoneNumber from) override;
    void handleDial(common::PhoneNumber) override {};
};

}
