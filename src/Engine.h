#ifndef ENGINE_H
#define ENGINE_H

#include "display/Renderer.h"

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

    private:
        SDL_Window* gameWindow_;
        Renderer* renderer_;

};

#endif // ENGINE_H
