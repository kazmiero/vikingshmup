#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <vector>
#include "InputEvent.h"

/// @file InputManager.h

/// @class InputManager
/// Do the game's event loop
class InputManager
{
    public:
        InputManager();
        virtual ~InputManager();

        bool eventLoop();
        events::InputEvent menuEventLoop();

        void clearEvents();
        const std::vector<events::InputEvent>& getEvents() const;
    protected:
    private:
        std::vector<events::InputEvent> events_;
};

#endif // INPUTMANAGER_H
