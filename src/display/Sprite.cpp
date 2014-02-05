#include "Sprite.h"
#include <iostream>
#include <SDL2/SDL_image.h>

Sprite::Sprite(const std::string& name, const std::string& type, SDL_Color transparencyColor, SDL_Renderer* renderer)
    : name_(name)
    , imgType_(type)
{
    std::string filename = name_+"."+imgType_;

    initFromFile(filename, transparencyColor, renderer);
}

Sprite::~Sprite()
{
    SDL_DestroyTexture(texture_);
}

SDL_Texture* Sprite::get() const
{
    return texture_;
}

bool Sprite::initFromFile(const std::string& filename, SDL_Color transparencyColor, SDL_Renderer* renderer)
{
    SDL_Surface* surface = IMG_Load(filename.c_str());
    if (surface == NULL)
    {
        std::cout << SDL_GetError() << std::endl;
        return false;
    }
    // set color key for transparency
	Uint32 colorKey = SDL_MapRGB(surface->format, transparencyColor.r, transparencyColor.g, transparencyColor.b);
	SDL_SetColorKey(surface, SDL_RLEACCEL | SDL_TRUE, colorKey);
    w_ = surface->w;
    h_ = surface->h;

    texture_ = SDL_CreateTextureFromSurface(renderer,surface);
    if (texture_ == NULL)
    {
        std::cout << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

int Sprite::getW() const
{
    return w_;
}

int Sprite::getH() const
{
    return h_;
}
