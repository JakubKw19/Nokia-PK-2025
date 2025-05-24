#include "Application.hpp"
#include "States/NotConnectedState.hpp"

namespace ue
{

Application::Application(common::PhoneNumber phoneNumber,
                         common::ILogger &iLogger,
                         IBtsPort &bts,
                         IUserPort &user,
                         ITimerPort &timer)
    : context{iLogger, bts, user, timer},
      logger(iLogger, "[APP] ")
{
    logger.logInfo("Started");
    context.setState<NotConnectedState>();
}

Application::~Application()
{
    logger.logInfo("Stopped");
}

void Application::handleTimeout()
{
    context.state->handleTimeout();
}

void Application::handleSib(common::BtsId btsId)
{
    context.state->handleSib(btsId);
}

void Application::handleAttachAccept()
{
    context.state->handleAttachAccept();
}

void Application::handleAttachReject()
{
    context.state->handleAttachReject();
}

void Application::handleComposeSms(common::PhoneNumber to, const std::string &text)
{
    context.state->handleComposeSms(to, text);
}

void Application::handleDisconnect()
{
    context.state->handleDisconnect();
}

void Application::handleCallAccepted(common::PhoneNumber from)
{
    context.state->handleCallAccepted(from);
}

void Application::handleCallDropped(common::PhoneNumber from)
{
    context.state->handleCallDropped(from);
}

void Application::handleUnknownRecipient(common::PhoneNumber from)
{
    context.state->handleUnknownRecipient(from);
}
void Application::handleCallRequest(common::PhoneNumber to)
{
    context.state->handleCallRequest(to);
}/*
void Application::handleCallRequest(common::PhoneNumber to)
{
    logger.logInfo("Handling call request to ", to);
    IBtsPort.sendCallRequest(to);
}*/


}
