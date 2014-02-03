#include "AABB.h"
#include <cmath>

AABB::AABB()
{
    pos_ = Vector2f();
    w_ = 0.0f;
    h_ = 0.0f;
}

AABB::AABB(int x, int y, int w, int h)
{
    pos_.x_ = float(x);
    pos_.y_ = float(y);
    w_ = float(w);
    h_ = float(h);
}

AABB::~AABB()
{
    //dtor
}

void AABB::setPos(Vector2f pos)
{
    pos_ = pos;
}

void AABB::move(Vector2f dp)
{
    pos_ += dp;
}

SDL_Rect AABB::getRect() const
{
    SDL_Rect rect;
    rect.h = (int) h_;
    rect.w = (int) w_;
    rect.x = (int) round(pos_.x_);
    rect.y = (int) round(pos_.y_);

    return rect;
}
