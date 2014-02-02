#include "Renderer.h"
#include <vector>
#include <iostream>

Renderer::Renderer(SDL_Window* window, int logicalWidth, int logicalHeight)
{
    sdlRenderer_ = SDL_CreateRenderer(window, -1, 0);
    SDL_RenderSetLogicalSize(sdlRenderer_, logicalWidth, logicalHeight);

    init();

    initSprites("../ressource/sprite");
}

Renderer::~Renderer()
{
    //dtor
    // no need to clear the SDL_Renderer : this is done by SDL_Quit in the Engine
}

void Renderer::initSprites(const std::string& spritesDir)
{
    // Todo : replace thus ugly hardcode
    std::vector<std::string> spriteNames;
    spriteNames.push_back("bg");
    spriteNames.push_back("player");
    spriteNames.push_back("enemy");
    spriteNames.push_back("bullet");
    spriteNames.push_back("obstacle");


    for (Uint32 i = 0; i < spriteNames.size(); i++)
    {
        sprites_[spriteNames[i]] = new Sprite(spritesDir+"/"+spriteNames[i], sdlRenderer_);
        std::cout << "Successfully loaded " << spriteNames[i] << std::endl;
    }
}

void Renderer::renderSprite(const SDL_Rect* AABB, const std::string& spriteName)
{
    SDL_RenderCopy(sdlRenderer_, sprites_[spriteName]->get(), NULL, AABB);
}

const std::map<std::string, Sprite*>& Renderer::getSprites() const
{
    return sprites_;
}

void Renderer::init()
{
    // set black as default color
    SDL_SetRenderDrawColor(sdlRenderer_, 0, 0, 0, 255);
	clear();
	sendToFramebuffer();
}

void Renderer::clear()
{
    SDL_RenderClear(sdlRenderer_);
}

void Renderer::sendToFramebuffer()
{
    SDL_RenderPresent(sdlRenderer_);
}

