#include "ConnectedState.hpp"
#include "ComposeSmsState.hpp"
#include "NotConnectedState.hpp"

namespace ue
{

ConnectedState::ConnectedState(Context &context)
    : BaseState(context, "ConnectedState")
{
    logger.logInfo("Connected");
    context.user.showConnected();
}

void ConnectedState::handleComposeSms(common::PhoneNumber to, const std::string &text) {
    context.setState<ComposeSmsState>(to, text);
}

void ConnectedState::handleDisconnect()
{
    context.setState<NotConnectedState>();
}

}
