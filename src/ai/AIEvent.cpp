#include "AIEvent.h"

AIEvent::AIEvent(Uint32 aiId, AICommand command) :
    aiId_(aiId),
    command_(command)
{
    //ctor
}

AIEvent::~AIEvent()
{
    //dtor
}
