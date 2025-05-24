#pragma once

#include "../../../Application/Ports/IBtsPort.hpp"
#include "gmock/gmock.h"

namespace ue {

class IBtsEventsHandlerMock : public IBtsEventsHandler {
public:
    MOCK_METHOD(void, handleSib, (common::BtsId), (override));
    MOCK_METHOD(void, handleAttachAccept, (), (override));
    MOCK_METHOD(void, handleAttachReject, (), (override));
    MOCK_METHOD(void, handleDisconnect, (), (override));
    MOCK_METHOD(void, handleCallAccepted, (common::PhoneNumber), (override));
    MOCK_METHOD(void, handleCallDropped, (common::PhoneNumber), (override));
    MOCK_METHOD(void, handleUnknownRecipient, (common::PhoneNumber), (override));
};

} 
