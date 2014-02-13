#include "Circle.h"

Circle::Circle() :
    center_(Vector2f()),
    radius_(0.0f),
    boundingAABB_(center_, 2.0f*radius_, 2.0f*radius_)
{
    //ctor
}

Circle::Circle(const Vector2f& center, float radius) :
    center_(center),
    radius_(radius),
    boundingAABB_(center_, 2.0f*radius_, 2.0f*radius_)
{
}

Circle::Circle(const AABB& aabb) :
    center_(aabb.getPos()),
    radius_(0.25f*(aabb.getH()+aabb.getW())),
    boundingAABB_(aabb)
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

void Circle::move(Vector2f dp)
{
    center_ += dp;
    boundingAABB_.move(dp);
}

const AABB& Circle::getBoundingAABB() const
{
    return boundingAABB_;
}
