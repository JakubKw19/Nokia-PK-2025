#pragma once

#include "BaseState.hpp"

namespace ue
{

class ViewSmsState : public BaseState
{
public:
    ViewSmsState(Context& context, const std::string& index);
    void handleViewSms(const std::string &index) override;

private:
    std::string smsIndex;

};



}
