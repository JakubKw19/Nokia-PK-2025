#pragma once

#include "ITimerPort.hpp"
#include "Logger/PrefixedLogger.hpp"
#include <thread>
#include <mutex>
#include <condition_variable>

namespace ue
{

class TimerPort : public ITimerPort
{
public:
    TimerPort(common::ILogger& logger);

    void start(ITimerEventsHandler& handler);
    void stop();

    // ITimerPort interface
    void startTimer(Duration duration) override;
    void stopTimer() override;

private:
    common::PrefixedLogger logger;
    ITimerEventsHandler* handler = nullptr;
    std::mutex timerMutex;
    std::condition_variable timerCv;
    bool timerRunning = false;
    std::unique_ptr<std::thread> timerThread;
};

}
