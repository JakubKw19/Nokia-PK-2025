#include "UserPort.hpp"
#include "UeGui/IListViewMode.hpp"
#include "UeGui/ISmsComposeMode.hpp"
#include "UeGui/ITextMode.hpp"
#include "Context.hpp"
#include "Smsdb.hpp"
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

void UserPort::showConnected()
{
    IUeGui::IListViewMode& menu = gui.setListViewMode();
    menu.clearSelectionList();
    menu.addSelectionListItem("Compose SMS", "");
    menu.addSelectionListItem("View SMS", "");
    gui.setAcceptCallback([this, &menu]() {
        auto [ok, index] = menu.getCurrentItemIndex();
        if (!ok) return;
        if (index == 0) {
            IUeGui::ISmsComposeMode& smsCompose = gui.setSmsComposeMode();
            gui.setAcceptCallback([this, &smsCompose]() {
                this->to = smsCompose.getPhoneNumber();
                this->message = smsCompose.getSmsText();
                
                // IUeGui::IListViewMode& menu = gui.setListViewMode();
                // std::string label = "To: " + common::to_string(this->to);
                // std::string text = this->message;
                // menu.addSelectionListItem(label, text);
                
                handler->handleComposeSms(this->to, this->message);
                smsCompose.clearSmsText();
                this->showConnected();
            });
            gui.setRejectCallback([this, &smsCompose]() {
                smsCompose.clearSmsText();
                this->showConnected();
            });
        }
        if (index == 1) {
            IUeGui::IListViewMode& smsList = gui.setListViewMode();
            smsList.clearSelectionList();
            this->showSmsList(handler->getAllSms());
            gui.setAcceptCallback([this, &smsList]() {
                auto [ok, index] = smsList.getCurrentItemIndex();
                if (!ok) return;

                auto messages = handler->getAllSms();
                if (index < 0 || index >= static_cast<int>(messages.size())) return;

                auto& selectedSms = messages[index];
                selectedSms.isRead = true;
                handler->markSmsAsRead(index);

                IUeGui::ITextMode& viewText = gui.setViewTextMode();
                viewText.setText(selectedSms.text);

                gui.setAcceptCallback([this]() {
                    this->showConnected();
                });
                gui.setRejectCallback([this]() {
                    this->showConnected();
                });
            });
            gui.setRejectCallback([this, &smsList]() {
                this->showConnected();
            });
        }
    });
}

void UserPort::showSmsList(const std::vector<ue::Sms>& messages)
{
    logger.logInfo("Showing SMS List (Count: ", messages.size(), ")");
    IUeGui::IListViewMode& menu = gui.setListViewMode();
    menu.clearSelectionList();
    for (const auto& sms : messages)
    {
        std::string prefix = sms.isRead ? "  " : "* "; 
        std::string label = prefix + "From: " + common::to_string(sms.from);
        std::string text = sms.text;
        menu.addSelectionListItem(label, sms.text); 
    }
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




