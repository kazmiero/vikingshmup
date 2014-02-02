#ifndef ENGINE_H
#define ENGINE_H

#include "display/Renderer.h"
#include "world/World.h"
#include "time/Timer.h"
#include "events/InputManager.h"

/// @file Engine.h

/// @class Engine
/// Game engine : top-level class managing the game experience
class Engine
{
    public:
        Engine();
        virtual ~Engine();

        bool initSDL();

        void dummyDrawing();

        void gameLoop();
        void renderWorld();
        void pushCommands();

    private:
        SDL_Window* gameWindow_;
        Renderer* renderer_;
        World* world_;
        Timer* fpsTimer_;
        InputManager* inputManager_;

        const float fps_;

};

#endif // ENGINE_H
