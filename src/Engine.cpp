#include "Engine.h"
#include <iostream>

Engine::Engine()
{
    initSDL();
    dummyDrawing();
}

Engine::~Engine()
{
    //dtor
}

bool Engine::initSDL()
{
    if (SDL_Init(SDL_INIT_VIDEO) == -1)
	{
		std::cout << SDL_GetError() << std::endl;
		return false;
	}

    atexit(SDL_Quit);

	gameWindow_ = SDL_CreateWindow(
		"Viking Shmup",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		600,
		600,
		SDL_WINDOW_SHOWN
	);
	if (gameWindow_ == NULL){
        std::cout << SDL_GetError() << std::endl;
        return false;
	}

	renderer_ = new Renderer(gameWindow_, 600, 600);

    return true;
}

void Engine::dummyDrawing()
{
    // TEST : drawing things
	renderer_->renderSprite(NULL, "bg");
	SDL_Rect playerAABB;
	playerAABB.x = 300;
	playerAABB.y = 300;
	playerAABB.w = 40;
	playerAABB.h = 40;
	renderer_->renderSprite(&playerAABB, "player");

	renderer_->sendToFramebuffer();

	SDL_Delay(2000);
}
