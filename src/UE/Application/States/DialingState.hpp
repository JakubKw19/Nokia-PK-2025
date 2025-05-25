#pragma once

#include "BaseState.hpp"
#include "Messages/PhoneNumber.hpp"

namespace ue
{

class DialingState : public BaseState
{
public:
    DialingState(Context& context, common::PhoneNumber callee);

    void handleCallAccepted(common::PhoneNumber from) override;
    void handleCallDropped(common::PhoneNumber from) override;
    void handleUnknownRecipient(common::PhoneNumber from) override;
    void handleTimeout() override;
    void handleUserReject();
    void handleDial(common::PhoneNumber) override {};
    void handleUserHangUp() override;

private:
    common::PhoneNumber callee;
};

}