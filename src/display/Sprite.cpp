#include "Sprite.h"
#include <iostream>

Sprite::Sprite(const std::string& name, SDL_Renderer* renderer)
    : name_(name)
{
    std::string BMPfilename = name + ".bmp";

    initFromBMP(BMPfilename, renderer);
}

Sprite::~Sprite()
{
    SDL_DestroyTexture(texture_);
}

SDL_Texture* Sprite::get() const
{
    return texture_;
}

bool Sprite::initFromBMP(const std::string& filename, SDL_Renderer* renderer)
{
    SDL_Surface* surface = SDL_LoadBMP(filename.c_str());
    if (surface == NULL)
    {
        std::cout << SDL_GetError() << std::endl;
        return false;
    }
    // set color key for transparency
	Uint32 colorKey = SDL_MapRGB(surface->format, 0, 0xFF, 0xFF);
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
