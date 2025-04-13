#include "ConnectedState.hpp"

namespace ue
{

ConnectedState::ConnectedState(Context &context)
    : BaseState(context, "ConnectedState")
{
    logger.logDebug("Connected");
    context.user.showConnected();
}

}
