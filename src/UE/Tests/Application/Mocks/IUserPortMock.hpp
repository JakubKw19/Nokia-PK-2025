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
    MOCK_METHOD(void, handleCallRequest, (common::PhoneNumber to), (override));

};

class IUserPortMock : public IUserPort
{
public:
    IUserPortMock();
    ~IUserPortMock() override;

    MOCK_METHOD(void, showNotConnected, (), (final));
    MOCK_METHOD(void, showConnecting, (), (final));
    MOCK_METHOD(void, showConnected, (), (final));
    MOCK_METHOD(void, showDialing, (common::PhoneNumber), (override));
    MOCK_METHOD(void, showMessage, (const std::string&), (override));
    MOCK_METHOD(void, handleCallRequest, (common::PhoneNumber to), (override));

};

}
