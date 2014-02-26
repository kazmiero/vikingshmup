#include "Renderer.h"
#include "ProgramConstants.h"
#include <vector>
#include <iostream>

Renderer::Renderer(SDL_Window* window, int logicalWidth, int logicalHeight)
{
    sdlRenderer_ = SDL_CreateRenderer(window, -1, 0);
    SDL_RenderSetLogicalSize(sdlRenderer_, logicalWidth, logicalHeight);

    init();

    initSprites(ProgramConstants::getInstance().getSpritesDir());
    initMenuSprites(ProgramConstants::getInstance().getMenusDir());
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
    spriteNames.push_back("player");
    spriteNames.push_back("enemy");
    spriteNames.push_back("bullet");
    spriteNames.push_back("bullet_enemy");
    spriteNames.push_back("obstacle");
    spriteNames.push_back("obstacle-long");
    spriteNames.push_back("cannon");

    SDL_Color transparencyColor;
    transparencyColor.r = 0, transparencyColor.g = 255, transparencyColor.b = 255, transparencyColor.a = 255;

    for (Uint32 i = 0; i < spriteNames.size(); i++)
    {
        sprites_[spriteNames[i]] = new Sprite(spritesDir+"/"+spriteNames[i], "bmp", transparencyColor, sdlRenderer_);
        std::cout << "Successfully loaded " << spriteNames[i] << std::endl;
    }

    spriteNames.push_back("bg");
    sprites_[spriteNames.back()] = new Sprite(spritesDir+"/"+spriteNames.back()+"2", "png", transparencyColor, sdlRenderer_);
    std::cout << "Successfully loaded bg" << std::endl;
}

void Renderer::initMenuSprites(const std::string& menuSpritesDir)
{
    // Todo : replace thus ugly hardcode
    std::vector<std::string> spriteNames;
    spriteNames.push_back("start");
    spriteNames.push_back("exit");
    spriteNames.push_back("continue");
    spriteNames.push_back("gameover");
    spriteNames.push_back("levelcleared");

    SDL_Color transparencyColor;
    transparencyColor.r = 0, transparencyColor.g = 0, transparencyColor.b = 0, transparencyColor.a = 0;

    for (Uint32 i = 0; i < spriteNames.size(); i++)
    {
        menuSprites_[spriteNames[i]] = new Sprite(menuSpritesDir+"/"+spriteNames[i], "png", transparencyColor, sdlRenderer_);
        std::cout << "Successfully loaded " << spriteNames[i] << std::endl;
    }
}

void Renderer::renderBG(const SDL_Rect* camera)
{
    SDL_RenderCopy(sdlRenderer_, sprites_["bg"]->get(), camera, NULL);
}

void Renderer::renderSprite(const SDL_Rect* AABB, const std::string& spriteName)
{
    SDL_RenderCopy(sdlRenderer_, sprites_[spriteName]->get(), NULL, AABB);
}

void Renderer::renderRotatedSprite(const SDL_Rect* AABB, const std::string& spriteName, const SDL_Point* rotationCenter, const double rotationAngleDegrees)
{
    SDL_RenderCopyEx(sdlRenderer_, sprites_[spriteName]->get(), NULL, AABB, rotationAngleDegrees, rotationCenter, SDL_FLIP_NONE);
}

void Renderer::renderMenuSprite(const SDL_Rect* AABB, const std::string& spriteName)
{
    SDL_RenderCopy(sdlRenderer_, menuSprites_[spriteName]->get(), NULL, AABB);
}

const std::map<std::string, Sprite*>& Renderer::getSprites() const
{
    return sprites_;
}

const std::map<std::string, Sprite*>& Renderer::getMenuSprites() const
{
    return menuSprites_;
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

