#ifndef AABB_H
#define AABB_H

#include <SDL2/SDL.h>
#include "Vector2f.h"

/// @file AABB.h

/// @class AABB
/// Axis Aligned Bounding Box, using the SDL_Rect struct to stock data
class AABB
{
    public:
        AABB();
        AABB(int x, int y, int w, int h);
        virtual ~AABB();

        void setPos(Vector2f pos);
        void move(Vector2f dp);
        SDL_Rect getRect() const;
    protected:
    private:
        Vector2f pos_;
        float w_, h_;
        SDL_Rect rect_;
};

#endif // AABB_H
