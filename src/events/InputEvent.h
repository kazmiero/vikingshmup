#ifndef INPUTEVENT_H
#define INPUTEVENT_H

/// @file InputEvent.h

namespace events
{
    typedef enum {Quit, Pause, MovePlayer, Shoot} InputEventId;

/// @class InputEvent
/// An event triggered by the mouse, and eventually sent to the world (MovePlayer, Shoot)
class InputEvent
{
    public:
        InputEvent(InputEventId id);
        InputEvent(InputEventId id, int x, int y);
        virtual ~InputEvent();

        InputEventId id_;
        int x_, y_;

    protected:
    private:
};

}

#endif // INPUTEVENT_H
