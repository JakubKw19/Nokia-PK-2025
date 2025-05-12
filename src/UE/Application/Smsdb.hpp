#ifndef SMSDB_H
#define SMSDB_H

#include "Messages/PhoneNumber.hpp"
#include <vector>
#include <string>

namespace ue
{

struct Sms
{
    common::PhoneNumber from;
    std::string text;
    bool isRead;

    Sms(common::PhoneNumber from, const std::string& text, bool isRead = false)
        : from(from), text(text), isRead(isRead) {}
};

class SmsDb
{
public:
    SmsDb() = default;
    int addSms(const Sms& sms);
    const std::vector<Sms>& getAllSms() const;
    void markAsRead(size_t index);

private:
    std::vector<Sms> smsList;
};

}

#endif