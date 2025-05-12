#include "NotConnectedState.hpp"
#include "ConnectingState.hpp"

namespace ue
{

NotConnectedState::NotConnectedState(Context &context)
    : BaseState(context, "NotConnectedState")
{
    logger.logInfo("Not Connected");
    context.user.showNotConnected();
}

void NotConnectedState::handleSib(common::BtsId btsId)
{
    using namespace std::chrono_literals;
    context.bts.sendAttachRequest(btsId);
    context.setState<ConnectingState>();
    context.timer.startTimer(500ms);
}


}
