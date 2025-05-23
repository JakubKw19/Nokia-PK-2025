#include "ConnectedState.hpp"
#include "ComposeSmsState.hpp"
#include "NotConnectedState.hpp"
#include "ViewSmsState.hpp"

namespace ue
{

ConnectedState::ConnectedState(Context &context)
    : BaseState(context, "ConnectedState")
{
    context.user.showConnected();
}

void ConnectedState::handleComposeSms(common::PhoneNumber to, const std::string &text) {
    context.setState<ComposeSmsState>(to, text);
    // context.state->handleComposeSms(to, text);
    context.setState<ConnectedState>();
}

const std::vector<Sms>& ConnectedState::getAllSms()
{
    const std::vector<Sms>& smsList = context.smsDb.getAllSms();
    return smsList;
}

void ConnectedState::handleViewSms(const std::string &index)
{
    context.setState<ViewSmsState>(index);
}

void ConnectedState::handleDisconnect()
{
    context.setState<NotConnectedState>();
}

void ConnectedState::handleSmsReceived(common::PhoneNumber from, std::string text)
{
    logger.logInfo("SMS received from: ", from); // Log removed text for brevity
    int smsIndex = context.smsDb.addSms(Sms{from, text});
    // logger.logDebug("SMS stored at index: ", smsIndex);
    // context.user.showNewSms(); // Show notification, but stay in main menu
}


}
