#pragma once

#include "Ports/ITimerPort.hpp"
#include "Ports/IBtsPort.hpp"
#include "Ports/IUserPort.hpp"


namespace ue
{

class IEventsHandler : public IBtsEventsHandler,
                       public IUserEventsHandler,
                       public ITimerEventsHandler
{
public:
    virtual void handleCallRequest(common::PhoneNumber to) = 0;
    
    using IUserEventsHandler::handleUserAccept;
    using IUserEventsHandler::handleUserReject;
    using IUserEventsHandler::handleUserHangUp;
};

}
