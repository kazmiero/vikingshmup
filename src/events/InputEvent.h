#ifndef INPUTEVENT_H
#define INPUTEVENT_H

namespace events
{
    typedef enum {Quit, MovePlayer, Shoot} InputEventId;

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
