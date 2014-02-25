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

        bool gameLoop();
        void renderWorld();
        void pushCommands();

        void renderTitleMenu(TitleMenuItem selectedMenuItem);
        void renderTextScreen(const std::string& spriteName, float duration);

    private:
        SDL_Window* gameWindow_;
        Renderer* renderer_;
        World* world_;
        Timer* fpsTimer_;
        InputManager* inputManager_;

        GameState state_;
};

#endif // ENGINE_H
