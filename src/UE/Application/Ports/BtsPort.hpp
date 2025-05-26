#pragma once

#include "IBtsPort.hpp"
#include "Logger/PrefixedLogger.hpp"
#include "ITransport.hpp"
#include "Messages/PhoneNumber.hpp"

namespace ue
{

    class BtsPort : public IBtsPort
    {
    public:
        BtsPort(common::ILogger& logger, common::ITransport& transport, common::PhoneNumber phoneNumber);
        void start(IBtsEventsHandler& handler);
        void stop();
        void sendCallRequest(common::PhoneNumber to) override;
        void sendCallDropped(common::PhoneNumber to) override;
        void sendAttachRequest(common::BtsId) override;
        void sendSms(common::PhoneNumber to, const std::string &text) override;
        void sendCallAccepted(common::PhoneNumber to);
        void showCallRequest(common::PhoneNumber from) override {}
        void showTalking(common::PhoneNumber interlocutor) override {}
        void sendCallTalk(common::PhoneNumber, const std::string&) override;
    private:
        void handleMessage(BinaryMessage msg);
        void handleDisconnect();

        common::PrefixedLogger logger;
        common::ITransport& transport;
        common::PhoneNumber phoneNumber;

        IBtsEventsHandler* handler = nullptr;
    };

}