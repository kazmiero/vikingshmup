#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>
#include <string>

///  @file Sprite.h

/// @class Sprite
/// Class describing a sprite, using a SDL_Texture
class Sprite
{
    public:
        Sprite(const std::string& name, const std::string& type, SDL_Color transparencyColor, SDL_Renderer* renderer);
        virtual ~Sprite();

        bool initFromFile(const std::string& filename, SDL_Color transparencyColor, SDL_Renderer* renderer);
        SDL_Texture* get() const;
        int getW() const;
        int getH() const;

    private:
        SDL_Texture* texture_;
        const std::string name_, imgType_;
        int w_, h_;

};

#endif // SPRITE_H
