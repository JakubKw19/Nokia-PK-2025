
#include "BaseState.hpp"
#include "Messages/PhoneNumber.hpp"

namespace ue
{

    class TalkingState : public BaseState
    {
    public:
        TalkingState(Context& context, common::PhoneNumber interlocutor);

        // Obsługa decyzji użytkownika
        void handleUserHangUp();

        // Obsługa wiadomości od BTS
        void handleCallAccepted(common::PhoneNumber from) override;
        void handleCallDropped(common::PhoneNumber from) override;
        void handleUnknownRecipient(common::PhoneNumber from) override;
        void handleCallRequest(common::PhoneNumber from) override;
        void handleDial(common::PhoneNumber) override {};
        void handleMessageSend(common::PhoneNumber to, const std::string &text) override;
        void handleReceiveCallTalk(common::PhoneNumber from, const std::string &text) override;

        // Obsługa timeoutu
        void handleTimeout() override;

    private:
        common::PhoneNumber interlocutor;
    };

}