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
};

}
