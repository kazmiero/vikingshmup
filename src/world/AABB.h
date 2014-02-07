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

        const Vector2f& getPos() const;
        float getW() const;
        float getH() const;

        static AABB camera;
    protected:
    private:
        Vector2f pos_;  ///< center of the AABB
        float w_, h_;   ///< width and height
};

#endif // AABB_H
