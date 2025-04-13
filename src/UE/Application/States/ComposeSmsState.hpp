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

private:
    common::PhoneNumber to;
    std::string message;
};



}
