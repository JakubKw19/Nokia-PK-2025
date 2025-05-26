#include "BaseState.hpp"
#include "Messages/PhoneNumber.hpp"

namespace ue
{

    class RingingState : public BaseState
    {
    public:
        RingingState(Context& context, common::PhoneNumber caller);

        void handleUserAccept();
        void handleUserReject();
        void handleCallAccepted(common::PhoneNumber from) override;
        void handleCallDropped(common::PhoneNumber from) override;
        void handleUnknownRecipient(common::PhoneNumber from) override;
        void handleTimeout() override;
        void handleDial(common::PhoneNumber) override {};

    private:
        common::PhoneNumber caller;
    };

}