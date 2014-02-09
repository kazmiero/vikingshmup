#include "Circle.h"

Circle::Circle() :
    center_(Vector2f()),
    radius_(0.0f)
{
    //ctor
}

Circle::Circle(const Vector2f& center, float radius) :
    center_(center),
    radius_(radius)
{
}

Circle::Circle(const AABB& aabb) :
    center_(aabb.getPos()),
    radius_(0.25f*(aabb.getH()+aabb.getW()))
{
}

Circle::~Circle()
{
    //dtor
}

const Vector2f& Circle::getCenter() const
{
    return center_;
}

float Circle::getRadius() const
{
    return radius_;
}
