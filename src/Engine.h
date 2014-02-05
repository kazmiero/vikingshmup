#ifndef ENGINE_H
#define ENGINE_H

#include "display/Renderer.h"
#include "world/World.h"
#include "time/Timer.h"
#include "events/InputManager.h"

/// @file Engine.h

/// @class Engine
/// Game engine : top-level class managing the game experience
typedef enum {Playing, Title, Paused} GameState;
typedef enum {Start, Exit} TitleMenuItem;

class Engine
{
    public:
        Engine();
        virtual ~Engine();

        bool initSDL();

        void dummyDrawing();

        void mainLoop();

        void play();
        TitleMenuItem titleMenu();

        void gameLoop();
        void renderWorld();
        void pushCommands();

        void renderTitleMenu(TitleMenuItem selectedMenuItem);

    private:
        SDL_Window* gameWindow_;
        Renderer* renderer_;
        World* world_;
        Timer* fpsTimer_;
        InputManager* inputManager_;

        GameState state_;
        const float fps_;
};

#endif // ENGINE_H
