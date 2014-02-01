#include "Timer.h"

Timer::Timer(float frequency) :
    currentTicks_(0),
    previousTicks_(0),
    frequency_(frequency)
{
}

Timer::~Timer()
{
    //dtor
}

void Timer::start()
{
    previousTicks_ = SDL_GetTicks();
}

void Timer::pause()
{
    currentTicks_ = SDL_GetTicks();
}

void Timer::reset()
{
    currentTicks_ = 0;
    previousTicks_ = 0;
}

Uint32 Timer::getWaitingTime()
{
    return (Uint32)(1000/frequency_) - (currentTicks_ - previousTicks_);
}