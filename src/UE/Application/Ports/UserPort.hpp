#pragma once

#include "IUserPort.hpp"
#include "Logger/PrefixedLogger.hpp"
#include "IUeGui.hpp"
#include "Messages/PhoneNumber.hpp"

namespace ue
{

class UserPort : public IUserPort
{
public:
    UserPort(common::ILogger& logger, IUeGui& gui, common::PhoneNumber phoneNumber);
    void start(IUserEventsHandler& handler);
    void stop();

    void showNotConnected() override;
    void showConnecting() override;
    void showConnected() override;
    void showSmsList(const std::vector<Sms>& messages) override;
    void showDialing(common::PhoneNumber to) override;
    void showMessage(const std::string& text) override;
    void showTalking(common::PhoneNumber interlocutor) override;
    void showCallRequest(common::PhoneNumber from) override;
    void handleDial(common::PhoneNumber to);
    void addMessageFromCall(common::PhoneNumber from, const std::string& text) override;
    void clearCallMode() override;
    // common::PhoneNumber getRecipientPhoneNumber() const
    // {
    //     return this->to;
    // }
    // string getSmsText() const
    // {
    //     return this->message;
    // }
private:
    common::PrefixedLogger logger;
    IUeGui& gui;
    common::PhoneNumber phoneNumber;
    IUserEventsHandler* handler = nullptr;
    common::PhoneNumber to;
    std::string message;
    IUeGui::ICallMode* callMode = nullptr;
};

}
