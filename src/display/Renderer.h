#ifndef RENDERER_H
#define RENDERER_H

#include "Sprite.h"
#include <map>

/// @file Renderer.h

/// @class Renderer
/// Class managing the shmup's 2D rendering, using the GPU-accelerated SDL_Renderer
class Renderer
{
    public:
        Renderer(SDL_Window* window, int logicalWidth, int logicalHeight);
        virtual ~Renderer();

        void init();
        void clear();
        void sendToFramebuffer();

        /// load all the images in the sprites directory, init the corresponding sprites and map them by name
        void initSprites(const std::string& spritesDir);
        void initMenuSprites(const std::string& menuSpritesDir);

        void renderSprite(const SDL_Rect* AABB, const std::string& spriteName);
        void renderRotatedSprite(const SDL_Rect* AABB, const std::string& spriteName, const SDL_Point* rotationCenter, const double rotationAngleDegrees);
        void renderMenuSprite(const SDL_Rect* AABB, const std::string& spriteName);

        const std::map<std::string, Sprite*>& getSprites() const;
        const std::map<std::string, Sprite*>& getMenuSprites() const;
    private:
        SDL_Renderer* sdlRenderer_;
        std::map<std::string, Sprite*> sprites_;
        std::map<std::string, Sprite*> menuSprites_;
};

#endif // RENDERER_H
