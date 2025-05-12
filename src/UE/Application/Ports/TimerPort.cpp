#include "TimerPort.hpp"
#include <chrono>
#include <thread>
#include <condition_variable>

namespace ue
{

TimerPort::TimerPort(common::ILogger &logger)
    : logger(logger, "[TIMER PORT]")
{}

void TimerPort::start(ITimerEventsHandler &handler)
{
    logger.logDebug("Started");
    this->handler = &handler;
}

void TimerPort::stop()
{
    logger.logDebug("Stoped");
    stopTimer();
    handler = nullptr;
}

void TimerPort::startTimer(Duration duration)
{
    logger.logDebug("Start timer: ", duration.count(), "ms");
    stopTimer();
    timerRunning = true;
    timerThread = std::make_unique<std::thread>(
        [this, duration]()
        {
            std::unique_lock<std::mutex> lock(timerMutex);
            if (timerCv.wait_for(lock, duration, [this]() { return !timerRunning; }))
            {
                logger.logDebug("Timer interrupted");
            }
            else if (timerRunning && handler)
            {
                handler->handleTimeout();
                logger.logInfo("Timer expired after: ", duration.count(), "ms");
            }
        });
}

void TimerPort::stopTimer()
{
    logger.logDebug("Stop timer");
    {
        std::lock_guard<std::mutex> lock(timerMutex);
        timerRunning = false;
    }
    timerCv.notify_all(); // Notify the thread to stop waiting
    if (timerThread && timerThread->joinable())
    {
        timerThread->join(); // Allow the thread to exit gracefully
    }
    timerThread.reset();
}

}
