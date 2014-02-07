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
    Vector2f relativePos = pos_ - AABB::camera.getPos() - Vector2f(w_/2, h_/2);

    rect.h = (int) h_;
    rect.w = (int) w_;
    rect.x = (int) round(relativePos.x_);
    rect.y = (int) round(relativePos.y_);

    return rect;
}

const Vector2f& AABB::getPos() const
{
    return pos_;
}

Vector2f AABB::getUpLeftCorner() const
{
    return pos_ - Vector2f(w_/2, h_/2);
}

float AABB::getW() const
{
    return w_;
}

float AABB::getH() const
{
    return h_;
}

AABB AABB::camera = AABB();
