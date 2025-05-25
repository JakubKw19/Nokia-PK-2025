#include "Application.hpp"
#include "States/NotConnectedState.hpp"
#include "Smsdb.hpp"

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

void Application::handleSmsSend()
{
    context.state->handleSmsSend();
}

void Application::handleAttachReject()
{
    context.state->handleAttachReject();
}

void Application::handleComposeSms(common::PhoneNumber to, const std::string &text)
{
    context.state->handleComposeSms(to, text);
}

const std::vector<Sms>& Application::getAllSms()
{
    return context.state->getAllSms();
}

void Application::handleViewSms(const std::string &index)
{
    context.state->handleViewSms(index);
}

void Application::handleSmsReceived(common::PhoneNumber from, std::string text)
{
    logger.logInfo("Received SMS from: " + common::to_string(from) + ", text: " + text);
    context.state->handleSmsReceived(from, text);
}

void Application::handleDisconnect()
{
    context.state->handleDisconnect();
}

void Application::markSmsAsRead(size_t index)
{
    context.state->markSmsAsRead(index);
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
}

void Application::handleUserAccept()
{
    context.state->handleUserAccept();
}

void Application::handleUserReject()
{
    context.state->handleUserReject();
}

void Application::handleUserHangUp()
{
    context.state->handleUserHangUp();
}

void Application::handleDial(common::PhoneNumber to)
{
    context.state->handleDial(to);
}

/*
void Application::handleCallRequest(common::PhoneNumber to)
{
    logger.logInfo("Handling call request to ", to);
    IBtsPort.sendCallRequest(to);
}*/


}
