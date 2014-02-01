#ifndef AABB_H
#define AABB_H

#include <SDL2/SDL.h>

/// @file AABB.h

/// @class AABB
/// Axis Aligned Bounding Box, using the SDL_Rect struct to stock data
class AABB
{
    public:
        AABB();
        AABB(int x, int y, int w, int h);
        virtual ~AABB();

        const SDL_Rect* get() const;
    protected:
    private:
        SDL_Rect rect_;
};

#endif // AABB_H
