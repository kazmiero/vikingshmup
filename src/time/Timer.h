#ifndef TIMER_H
#define TIMER_H

#include <SDL2/SDL.h>

class Timer
{
    public:
        Timer(float frequency);
        virtual ~Timer();

        Uint32 getWaitingTime();
        void reset();
        void start();
        void pause();
    protected:
    private:
        Uint32 currentTicks_, previousTicks_;
        float frequency_; // or fps

};

#endif // TIMER_H
