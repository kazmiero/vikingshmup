#ifndef AIEVENT_H
#define AIEVENT_H

#include <SDL2/SDL.h>

typedef enum {Move, Shoot} AICommand;

class AIEvent
{
    public:
        AIEvent(Uint32 id, AICommand command);
        virtual ~AIEvent();

        Uint32 aiId_;
        AICommand command_;
};

#endif // AIEVENT_H
