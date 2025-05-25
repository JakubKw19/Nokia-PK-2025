#pragma once

#include "BaseState.hpp"
#include "Messages/PhoneNumber.hpp"

namespace ue
{

    class RingingState : public BaseState
    {
    public:
        RingingState(Context& context, common::PhoneNumber caller);

        // Obsługa decyzji użytkownika
        void handleUserAccept();
        void handleUserReject();

        // Obsługa wiadomości od BTS
        void handleCallAccepted(common::PhoneNumber from) override;
        void handleCallDropped(common::PhoneNumber from) override;
        void handleUnknownRecipient(common::PhoneNumber from) override;

        // Obsługa timeoutu
        void handleTimeout() override;

    private:
        common::PhoneNumber caller;
    };

}