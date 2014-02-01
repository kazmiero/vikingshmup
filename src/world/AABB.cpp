#include "AABB.h"

AABB::AABB()
{
    rect_.x = 0;
    rect_.y = 0;
    rect_.w = 0;
    rect_.h = 0;
}

AABB::AABB(int x, int y, int w, int h)
{
    rect_.x = x;
    rect_.y = y;
    rect_.w = w;
    rect_.h = h;
}

AABB::~AABB()
{
    //dtor
}

const SDL_Rect* AABB::get() const
{
    return &rect_;
}