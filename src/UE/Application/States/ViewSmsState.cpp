#include "ViewSmsState.hpp"
#include <IUeGui.hpp>
#include <UeGui/ISmsComposeMode.hpp>


namespace ue
{
    ViewSmsState::ViewSmsState(Context &context, const std::string& index)
    : BaseState(context, "ViewSmsState"), smsIndex(index)
{
    this->smsIndex = index;
    // logger.logInfo("Compose SMS to: " + common::to_string(to) + ", text: " + text);
}

    void ViewSmsState::handleViewSms(const std::string &index)
    {
        context.smsDb.getAllSms();
        logger.logInfo("View SMS: " + index);
        
    }

}
