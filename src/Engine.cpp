#include "Engine.h"
#include "ProgramConstants.h"
#include <iostream>

Engine::Engine() :
    state_(Title)
{
    world_ = new World();
    initSDL();
    fpsTimer_ = new Timer(ProgramConstants::getInstance().getFps());
    inputManager_ = new InputManager();

    mainLoop();
}

Engine::~Engine()
{
    //dtor
}

void Engine::mainLoop()
{
    while(true)
    {
        TitleMenuItem state = titleMenu();
        if (state == Start)
            play();
        else if (state == Exit)
            return;
    }
}

TitleMenuItem Engine::titleMenu()
{
    TitleMenuItem selectedMenuItem = Start; // 0 for start, 1 for exit

    while(true)
    {
        fpsTimer_->reset();
        fpsTimer_->start();

        events::InputEvent event = inputManager_->menuEventLoop();
        if (event.id_ == events::Quit)
            return Exit;
        else if (event.id_ == events::SelectMenu)
            return selectedMenuItem;
        else if (event.id_ == events::ChangeMenu)
        {
            if (selectedMenuItem == Exit)
                selectedMenuItem = Start;
            else
                selectedMenuItem = Exit;
        }

        renderTitleMenu(selectedMenuItem);

        fpsTimer_->pause();
        Uint32 delay = fpsTimer_->getWaitingTime();
        SDL_Delay(delay);
    }
}

void Engine::play()
{
    world_->setupLevel();
    gameLoop();

    // Todo: replace this by something clean
    world_->clearElements();
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
		ProgramConstants::getInstance().getCameraWidth(),
		ProgramConstants::getInstance().getCameraHeight(),
		SDL_WINDOW_SHOWN
	);
	if (gameWindow_ == NULL){
        std::cout << SDL_GetError() << std::endl;
        return false;
	}

	renderer_ = new Renderer(gameWindow_, ProgramConstants::getInstance().getCameraWidth(), ProgramConstants::getInstance().getCameraHeight());

	// create spritesAABB map
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
        if (world_->doCollisionCheck())
            return;
        world_->scroll();

        // graphics
        renderWorld();

        inputManager_->clearEvents();
        // trick for the relative mode in linux
        SDL_WarpMouseInWindow(gameWindow_, ProgramConstants::getInstance().getCameraWidth()/2, ProgramConstants::getInstance().getCameraHeight()/2);

        fpsTimer_->pause();
        Uint32 delay = fpsTimer_->getWaitingTime();

        SDL_Delay(delay);
        //std::cout << delay << std::endl;
    }
}

void Engine::renderWorld()
{
    renderer_->clear();

    // draw bg
    SDL_Rect camera;
    camera.x = AABB::camera.getPos().x_;
    camera.y = AABB::camera.getPos().y_;
    camera.w = 600, camera.h = 600;
    renderer_->renderBG(&camera);

    // draw player
    const Player* player = world_->getPlayer();
    SDL_Rect rect = player->getAABB().getRect();
    renderer_->renderSprite(&rect, player->getSpriteName());
    // draw cannon
    SDL_Rect cannonRect = player->getCannonAABB().getRect();
    SDL_Point rotationCenter = player->getRotationCenter();
    double orientation = player->getCannonOrientation();
    renderer_->renderRotatedSprite(&cannonRect, player->getCannonSpriteName(), &rotationCenter, orientation);

    // draw elements
    for (Uint32 elementIndex = 0; elementIndex < world_->getElementsToDraw().size(); elementIndex++)
    {
        const Element* element = world_->getElementsToDraw()[elementIndex];
        SDL_Rect rect = element->getAABB().getRect();
        renderer_->renderRotatedSprite(&rect, element->getSpriteName(), NULL, element->getRotation());
    }

    renderer_->sendToFramebuffer();
}

void Engine::renderTitleMenu(TitleMenuItem selectedMenuItem)
{
    renderer_->clear();

    const Sprite* start = renderer_->getMenuSprites().at("start");
    if (selectedMenuItem == Start)
        SDL_SetTextureColorMod(start->get(), 255, 0, 0);
    else
        SDL_SetTextureColorMod(start->get(), 255, 255, 255);
    SDL_Rect rect;
    rect.x = 100, rect.y = 200, rect.h = start->getH(), rect.w = start->getW();
    renderer_->renderMenuSprite(&rect,"start");

    const Sprite* exit = renderer_->getMenuSprites().at("exit");
    if (selectedMenuItem == Exit)
        SDL_SetTextureColorMod(exit->get(), 255, 0, 0);
    else
        SDL_SetTextureColorMod(exit->get(), 255, 255, 255);
    rect.x = 100, rect.y = 300, rect.h = exit->getH(), rect.w = exit->getW();
    renderer_->renderMenuSprite(&rect, "exit");

    renderer_->sendToFramebuffer();
}

void Engine::pushCommands()
{
    for (Uint32 i = 0; i < inputManager_->getEvents().size(); i++)
    {
        events::InputEvent event = inputManager_->getEvents()[i];
        if (event.id_ == events::MovePlayer
            || event.id_ == events::OrientCannon
            || event.id_ == events::Shoot)
            world_->addInputEvent(event);
    }
}
