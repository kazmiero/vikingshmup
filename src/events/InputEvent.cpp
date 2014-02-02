#include "InputEvent.h"

using namespace events;

InputEvent::InputEvent(InputEventId id) :
    id_(id),
    x_(0),
    y_(0)
{
}

InputEvent::InputEvent(InputEventId id, int x, int y) :
    id_(id),
    x_(x),
    y_(y)
{
    //ctor
}

InputEvent::~InputEvent()
{
    //dtor
}
