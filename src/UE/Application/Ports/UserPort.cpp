#include "UserPort.hpp"
#include "UeGui/IListViewMode.hpp"
#include "UeGui/ISmsComposeMode.hpp"
#include "Context.hpp"
#include "UeGui/IDialMode.hpp"

using std::string;


namespace ue
{

UserPort::UserPort(common::ILogger &logger, IUeGui &gui, common::PhoneNumber phoneNumber)
    : logger(logger, "[USER-PORT]"),
      gui(gui),
      phoneNumber(phoneNumber)
{}

void UserPort::start(IUserEventsHandler &handler)
{
    this->handler = &handler;
    gui.setTitle("Nokia " + to_string(phoneNumber));
}

void UserPort::stop()
{
    handler = nullptr;
}

void UserPort::showNotConnected()
{
    gui.showNotConnected();
}

void UserPort::showConnecting()
{
    gui.showConnecting();
}

void UserPort::showDialing(common::PhoneNumber to)
{
    IUeGui::IDialMode& dialMode = gui.setDialMode();
    logger.logInfo("Dialing: ", to);
}

void UserPort::showMessage(const std::string& text)
{
    logger.logInfo("Message to user: ", text);
    IUeGui::IListViewMode& view = gui.setListViewMode();
    view.clearSelectionList();
    view.addSelectionListItem("Message", text);
}

void UserPort::handleCallRequest(common::PhoneNumber to) {

    logger.logInfo("Call Request: ", to);
}

void UserPort::showConnected()
{
    IUeGui::IListViewMode& menu = gui.setListViewMode();
    menu.clearSelectionList();
    menu.addSelectionListItem("Compose SMS", "");
    menu.addSelectionListItem("View SMS", "");
    menu.addSelectionListItem("Request Call", "");
    gui.setAcceptCallback([this, &menu]() {
        auto [ok, index] = menu.getCurrentItemIndex();
        if (!ok) return;
        if (index == 0) {
            IUeGui::ISmsComposeMode& smsCompose = gui.setSmsComposeMode();
            gui.setAcceptCallback([this, &smsCompose]() {
                this->to = smsCompose.getPhoneNumber();
                this->message = smsCompose.getSmsText();
                logger.logInfo("Compose SMS to: " + common::to_string(to) + ", text: " + message);
                handler->handleComposeSms(this->to, this->message);
            });
        } else if (index == 2) {
            IUeGui::IDialMode& dialMode = gui.setDialMode();
            gui.setAcceptCallback([this, &dialMode]() {
                this->to = dialMode.getPhoneNumber();
                logger.logInfo("Request Call to: " + common::to_string(to));
                handler->handleCallRequest(this->to);
            });
        }

    });
}
}
// common::PhoneNumber UserPort::getRecipientPhoneNumber() const
// {
//     return this->to;
// }

// string UserPort::getSmsText() const
// {
//     return this->message;
// }




