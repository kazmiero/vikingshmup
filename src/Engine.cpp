#include "Engine.h"
#include <iostream>

Engine::Engine() :
    fps_(60.0f)
{
    world_ = new World(fps_);
    initSDL();
    world_->setupLevel();
    fpsTimer_ = new Timer(fps_);
    inputManager_ = new InputManager();

    //dummyDrawing();
    gameLoop();
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
		world_->getCameraWidth(),
		world_->getCameraHeight(),
		SDL_WINDOW_SHOWN
	);
	if (gameWindow_ == NULL){
        std::cout << SDL_GetError() << std::endl;
        return false;
	}

	renderer_ = new Renderer(gameWindow_, world_->getCameraWidth(), world_->getCameraHeight());

	// create spritesAABB map
	SDL_Delay(10);
	std::map<std::string,AABB> spritesAABB;
    for (std::map<std::string,Sprite*>::const_iterator it = renderer_->getSprites().begin(); it != renderer_->getSprites().end(); ++it)
    {
        AABB aabb(0,0,it->second->getW(), it->second->getH());
        spritesAABB[it->first] = aabb;
    }
    world_->setSpritesAABB(spritesAABB);

    if (SDL_SetRelativeMouseMode(SDL_TRUE) != 0)
	{
        std::cout << SDL_GetError() << std::endl;
        return false;
	}

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
	renderer_->renderSprite(&playerAABB, "obstacle");

	renderer_->sendToFramebuffer();

	SDL_Delay(2000);
}

void Engine::gameLoop()
{
    while(true)
    {
        fpsTimer_->reset();
        fpsTimer_->start();

        // get events
        if (!inputManager_->eventLoop())
            return;
        pushCommands();

        // world & physics
        world_->update();
        world_->doCollisionCheck();
        world_->scroll();

        // graphics
        renderWorld();

        inputManager_->clearEvents();
        // trick for the relative mode in linux
        SDL_WarpMouseInWindow(gameWindow_, world_->getCameraWidth()/2, world_->getCameraHeight()/2);

        fpsTimer_->pause();
        Uint32 delay = fpsTimer_->getWaitingTime();

        SDL_Delay(delay);
        //std::cout << delay << std::endl;
    }
}

void Engine::renderWorld()
{
    renderer_->clear();
    for (Uint32 elementIndex = 0; elementIndex < world_->getElementsToDraw().size(); elementIndex++)
    {
        const Element* element = world_->getElementsToDraw()[elementIndex];
        SDL_Rect rect = element->getAABB().getRect();
        renderer_->renderSprite(&rect, element->getSpriteName());
    }
    renderer_->sendToFramebuffer();
}

void Engine::pushCommands()
{
    for (Uint32 i = 0; i < inputManager_->getEvents().size(); i++)
    {
        events::InputEvent event = inputManager_->getEvents()[i];
        if (event.id_ != (events::Quit | events::Pause))
            world_->addInputEvent(event);
    }
}
