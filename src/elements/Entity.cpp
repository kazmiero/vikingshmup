#include "Entity.h"

Entity::Entity() :
    Element(),
    dp_(Vector2f()),
    velocity_(0.0f),
    maxVelocity_(0.0f)
{
    //ctor
}

Entity::Entity(const AABB& aabb, const std::string &spriteName, float maxVelocity) :
    Element(aabb, spriteName),
    dp_(Vector2f()),
    velocity_(0.0f),
    maxVelocity_(maxVelocity)
{
}

Entity::~Entity()
{
    //dtor
}

void Entity::move()
{
    aabb_.move(dp_);
}

void Entity::setSpeed(Vector2f dp)
{
    dp_ = dp;
}

void Entity::setSpeed(float dx, float dy)
{
    dp_.x_ = dx;
    dp_.y_ = dy;
}

float Entity::getMaxVelocity() const
{
    return maxVelocity_;
}
