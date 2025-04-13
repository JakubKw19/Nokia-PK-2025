#pragma once
#include "Messages/PhoneNumber.hpp"
#include "IUeGui.hpp"


namespace ue
{

class IUserEventsHandler
{
public:
    virtual ~IUserEventsHandler() = default;
    virtual void handleComposeSms(common::PhoneNumber to, const std::string &text) = 0;
};

class IUserPort
{
public:
    virtual ~IUserPort() = default;
    virtual void showNotConnected() = 0;
    virtual void showConnecting() = 0;
    virtual void showConnected() = 0;
    // virtual common::PhoneNumber getRecipientPhoneNumber() const = 0;
    // virtual std::string getSmsText() const = 0;
};

}
