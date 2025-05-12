#include "Smsdb.hpp"

namespace ue
{

int SmsDb::addSms(const Sms& sms)
{
    smsList.push_back(sms);
    return smsList.size() - 1;
}

const std::vector<Sms>& SmsDb::getAllSms() const
{
    return smsList;
}

void SmsDb::markAsRead(size_t index)
{
    if (index < smsList.size())
    {
        smsList[index].isRead = true;
    }
}

}