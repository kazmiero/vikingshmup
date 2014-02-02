#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <vector>
#include "InputEvent.h"

class InputManager
{
    public:
        InputManager();
        virtual ~InputManager();

        bool eventLoop();

        void clearEvents();
        const std::vector<events::InputEvent>& getEvents() const;
    protected:
    private:
        std::vector<events::InputEvent> events_;
};

#endif // INPUTMANAGER_H
