#pragma once

#include <gmock/gmock.h>
#include "Ports/IUserPort.hpp"

namespace ue
{

class IUserEventsHandlerMock : public IUserEventsHandler
{
public:
    IUserEventsHandlerMock();
    ~IUserEventsHandlerMock() override;
    MOCK_METHOD(void, handleComposeSms, (common::PhoneNumber to, const std::string &text), (override));
    MOCK_METHOD(void, handleViewSms, (const std::string &index), (override));
    MOCK_METHOD(const std::vector<Sms>&, getAllSms, (), (override));
    MOCK_METHOD(void, handleSmsSend, (), (override));
    MOCK_METHOD(void, markSmsAsRead, (size_t index), (override));
    MOCK_METHOD(void, handleDial, (common::PhoneNumber to), (override));
    MOCK_METHOD(void, handleUserAccept, (), (override));
    MOCK_METHOD(void, handleUserReject, (), (override));
    MOCK_METHOD(void, handleUserHangUp, (), (override));
    MOCK_METHOD(void, handleMessageSend, (common::PhoneNumber to, const std::string &text), (override));
};

class IUserPortMock : public IUserPort
{
public:
    IUserPortMock();
    ~IUserPortMock() override;

    MOCK_METHOD(void, showNotConnected, (), (final));
    MOCK_METHOD(void, showConnecting, (), (final));
    MOCK_METHOD(void, showConnected, (), (final));
    MOCK_METHOD(void, showSmsList, (const std::vector<Sms>& messages), (final));
    MOCK_METHOD(void, showDialing, (common::PhoneNumber), (override));
    MOCK_METHOD(void, showMessage, (const std::string&), (override));
    MOCK_METHOD(void, showCallRequest, (common::PhoneNumber), (override));
    MOCK_METHOD(void, showTalking, (common::PhoneNumber), (override));
};

}
