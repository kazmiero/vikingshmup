#ifndef TIMER_H
#define TIMER_H

#include <SDL2/SDL.h>

/// @file Timer.h

/// @class Timer
/// Basic class for time management. It works like a chronometer and provides the waiting time (according to the defined frequency_)
class Timer
{
    public:
        Timer(float frequency);
        virtual ~Timer();

        Uint32 getWaitingTime();
        bool hasTicked();

        void reset();
        void start();
        void pause();
    protected:
    private:
        Uint32 currentTicks_, previousTicks_;
        float frequency_; // or fps

};

#endif // TIMER_H
