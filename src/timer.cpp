#include "timer.h"

Timer::Timer(double duration) : elapsedTime(0), duration(duration)
{
}

void Timer::update(double deltaTime)
{
    elapsedTime += deltaTime;
    if (elapsedTime > duration)
    {
        elapsedTime = duration;
    }
}

void Timer::reset()
{
    elapsedTime = 0;
}

bool Timer::isFinished() const
{
    return elapsedTime >= duration;
}
