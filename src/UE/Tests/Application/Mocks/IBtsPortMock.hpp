#pragma once

#include <gmock/gmock.h>
#include "Ports/IBtsPort.hpp"
#include "Smsdb.hpp"

namespace ue
{

class IBtsEventsHandlerMock : public IBtsEventsHandler
{
public:
    IBtsEventsHandlerMock();
    ~IBtsEventsHandlerMock() override;

    MOCK_METHOD(void, handleSib, (common::BtsId), (final));
    MOCK_METHOD(void, handleAttachAccept, (), (final));
    MOCK_METHOD(void, handleAttachReject, (), (final));
    // MOCK_METHOD(void, handleComposeSms, (common::PhoneNumber, const std::string &), (final));
    MOCK_METHOD(void, handleDisconnect, (), (final));
    MOCK_METHOD(void, handleSmsReceived, (common::PhoneNumber, std::string), (override));
    MOCK_METHOD(void, handleCallAccepted, (common::PhoneNumber), (override));
    MOCK_METHOD(void, handleCallDropped, (common::PhoneNumber), (override));
    MOCK_METHOD(void, handleUnknownRecipient, (common::PhoneNumber), (override));
    MOCK_METHOD(void, handleCallRequest, (common::PhoneNumber from), (override));
    MOCK_METHOD(void, handleUserAccept, (), (override));
    MOCK_METHOD(void, handleUserReject, (), (override));
    MOCK_METHOD(void, handleUserHangUp, (), (override));
};

class IBtsPortMock : public IBtsPort
{
public:
    IBtsPortMock();
    ~IBtsPortMock() override;

    MOCK_METHOD(void, sendAttachRequest, (common::BtsId), (final));
    MOCK_METHOD(void, sendSms, (common::PhoneNumber, const std::string &), (override));
    MOCK_METHOD(void, sendCallRequest, (common::PhoneNumber), (override));
    MOCK_METHOD(void, sendCallDropped, (common::PhoneNumber), (override));
    MOCK_METHOD(void, sendCallAccepted, (common::PhoneNumber), (override));
    MOCK_METHOD(void, showCallRequest, (common::PhoneNumber), (override));
    MOCK_METHOD(void, showTalking, (common::PhoneNumber), (override));
};

}
