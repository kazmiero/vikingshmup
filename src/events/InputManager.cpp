#include <SDL2/SDL.h>
#include "InputManager.h"

InputManager::InputManager()
{
    //ctor
}

InputManager::~InputManager()
{
    //dtor
}

bool InputManager::eventLoop()
{
    using namespace events;

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        // event handling
		if (event.type == SDL_QUIT)
		{
			events_.push_back(InputEvent(Quit));
			return false;
        }

		// mouse move
		if (event.type == SDL_MOUSEMOTION)
			events_.push_back(InputEvent(MovePlayer, event.motion.xrel, event.motion.yrel));

        // mouse left click
		if (SDL_GetMouseState(NULL,NULL)&SDL_BUTTON(1))
            events_.push_back(InputEvent(Shoot));
    }

    return true;
}

const std::vector<events::InputEvent>& InputManager::getEvents() const
{
    return events_;
}

void InputManager::clearEvents()
{
    events_.clear();
}
