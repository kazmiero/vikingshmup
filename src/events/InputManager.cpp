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

events::InputEvent InputManager::menuEventLoop()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        // event handling
		if (event.type == SDL_QUIT)
			return events::InputEvent(events::Quit);

        if (event.type == SDL_KEYDOWN)
        {
            SDL_Keycode keyPressed = event.key.keysym.sym;

            if (keyPressed == SDLK_ESCAPE)
                return events::InputEvent(events::Quit);
            else if (keyPressed == SDLK_RETURN)
                return events::InputEvent(events::SelectMenu);
            else if (keyPressed == SDLK_UP ||keyPressed == SDLK_DOWN)
                return events::InputEvent(events::ChangeMenu);
        }
    }

    return events::InputEvent(events::None);
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

        if (event.type == SDL_KEYDOWN)
        {
            SDL_Keycode keyPressed = event.key.keysym.sym;
            if (keyPressed == SDLK_ESCAPE)
            {
                events_.push_back(InputEvent(Quit));
                return false;
            }
        }
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
