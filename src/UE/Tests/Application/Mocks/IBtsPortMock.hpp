#pragma once

#include <gmock/gmock.h>
#include "Ports/IBtsPort.hpp"
#include "IBtsEventsHandlerMock.hpp"

namespace ue
{

class IBtsPortMock : public IBtsPort
{
public:
    IBtsPortMock();
    ~IBtsPortMock() override;

    MOCK_METHOD(void, sendAttachRequest, (common::BtsId), (final));
    MOCK_METHOD(void, sendSms, (common::PhoneNumber, const std::string &), (override));
    MOCK_METHOD(void, sendCallRequest, (common::PhoneNumber), (override));
    MOCK_METHOD(void, sendCallDropped, (common::PhoneNumber), (override));
};

}
