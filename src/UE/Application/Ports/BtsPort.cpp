#include "BtsPort.hpp"
#include "Messages/IncomingMessage.hpp"
#include "Messages/OutgoingMessage.hpp"

namespace ue
{

BtsPort::BtsPort(common::ILogger &logger, common::ITransport &transport, common::PhoneNumber phoneNumber)
    : logger(logger, "[BTS-PORT]"),
      transport(transport),
      phoneNumber(phoneNumber)
{}

void BtsPort::start(IBtsEventsHandler &handler)
{
    transport.registerMessageCallback([this](BinaryMessage msg) {handleMessage(msg);});
    transport.registerDisconnectedCallback([this]() {handleDisconnect();});
    this->handler = &handler;
}

void BtsPort::stop()
{
    transport.registerMessageCallback(nullptr);
    transport.registerDisconnectedCallback(nullptr);
    handler = nullptr;
}

void BtsPort::handleMessage(BinaryMessage msg)
{
    try
    {
        common::IncomingMessage reader{msg};
        auto msgId = reader.readMessageId();
        auto from = reader.readPhoneNumber();
        auto to = reader.readPhoneNumber();

        switch (msgId)
        {
        case common::MessageId::Sib:
        {
            auto btsId = reader.readBtsId();
            handler->handleSib(btsId);
            break;
        }
        case common::MessageId::AttachResponse:
        {
            bool accept = reader.readNumber<std::uint8_t>() != 0u;
            if (accept)
                handler->handleAttachAccept();
            else
                handler->handleAttachReject();
            break;
        }
        case common::MessageId::CallAccepted:
        {
            handler->handleCallAccepted(from);
            break;
        }
        case common::MessageId::CallRequest:
        {
            handler->handleCallRequest(from);
            break;
        }
        case common::MessageId::CallDropped:
        {
            handler->handleCallDropped(from);
            break;
        }
        case common::MessageId::UnknownRecipient:
        {
            auto messageHeader = reader.readMessageHeader();
            switch (messageHeader.messageId) {
            case common::MessageId::Sms:
                logger.logError("Failed to send SMS – Recipient not found: ",
                                messageHeader.to);
                break;
            case common::MessageId::CallRequest:
                logger.logError("Failed to send call request – Recipient not found: ",
                                messageHeader.to);
                handler->handleUnknownRecipient(messageHeader.to);
                break;
            case common::MessageId::CallTalk:
                logger.logError("Failed to send call request – Recipient not found: ",
                                messageHeader.to);
                break;
            default:
                logger.logError("Failed to send message – Recipient not found: ",
                                messageHeader.to);
                break;
            }
            break;
            
        }
        case common::MessageId::Sms:
            {
                std::string text = reader.readRemainingText();
                handler->handleSmsReceived(from, text);
                break;
            }
        case common::MessageId::CallTalk:
        {
            std::string text = reader.readRemainingText();
            handler->handleReceiveCallTalk(from, text);
            break;
        }
        default:
            logger.logError("unknow message: ", msgId, ", from: ", from);

        }
    }
    catch (std::exception const& ex)
    {
        logger.logError("handleMessage error: ", ex.what());
    }
}


void BtsPort::sendAttachRequest(common::BtsId btsId)
{
    logger.logDebug("sendAttachRequest: ", btsId);
    common::OutgoingMessage msg{common::MessageId::AttachRequest,
                                phoneNumber,
                                common::PhoneNumber{}};
    msg.writeBtsId(btsId);
    transport.sendMessage(msg.getMessage());


}

void BtsPort::sendSms(common::PhoneNumber to, const std::string &text)
{
    logger.logInfo("Sending SMS to: ", to);
    common::OutgoingMessage msg{common::MessageId::Sms,
                                phoneNumber,
                                to};
    msg.writeText(text);
    transport.sendMessage(msg.getMessage());
}

void BtsPort::sendCallTalk(common::PhoneNumber to, const std::string& text)
{
    common::OutgoingMessage msg(common::MessageId::CallTalk, phoneNumber, to);
    msg.writeText(text);
    transport.sendMessage(msg.getMessage());
}


void BtsPort::handleDisconnect()
{
    logger.logInfo("handleDisconnect");
    if (handler)
        handler->handleDisconnect();
    else
        logger.logError("handleDisconnect: handler is nullptr");
}

void BtsPort::sendCallRequest(common::PhoneNumber to)
{
    logger.logInfo("Sending CallRequest to: ", to);
    common::OutgoingMessage msg{common::MessageId::CallRequest, phoneNumber, to};
    msg.writeNumber<std::uint8_t>(0);
    transport.sendMessage(msg.getMessage());
}

void BtsPort::sendCallDropped(common::PhoneNumber to)
{
    logger.logInfo("Sending CallDropped to: ", to);
    common::OutgoingMessage msg{common::MessageId::CallDropped, phoneNumber, to};
    transport.sendMessage(msg.getMessage());
}

void BtsPort::sendCallAccepted(common::PhoneNumber to)
{
    logger.logInfo("Sending CallAccepted to: ", to);
    common::OutgoingMessage msg{common::MessageId::CallAccepted, phoneNumber, to};
    transport.sendMessage(msg.getMessage());
}

}
