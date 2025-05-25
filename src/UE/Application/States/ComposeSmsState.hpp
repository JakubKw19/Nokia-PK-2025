#pragma once

#include "BaseState.hpp"
#include "Messages/PhoneNumber.hpp"

namespace ue
{

class ComposeSmsState : public BaseState
{
public:
    ComposeSmsState(Context& context, common::PhoneNumber to, const std::string &text);
    void handleComposeSms(common::PhoneNumber to, const std::string &text);
    void start();
    void handleSmsSend() override;
    void handleCallAccepted(common::PhoneNumber from) override;
    void handleCallDropped(common::PhoneNumber from) override;
    void handleUnknownRecipient(common::PhoneNumber from) override;
private:
    common::PhoneNumber to;
    std::string message;
};



}
