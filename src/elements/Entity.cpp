#include "Entity.h"

Entity::Entity() :
    Element(),
    dx_(0),
    dy_(0),
    velocity_(0.0f),
    maxVelocity_(0.0f)
{
    //ctor
}

Entity::Entity(const AABB& aabb, const std::string &spriteName, float maxVelocity) :
    Element(aabb, spriteName),
    dx_(0),
    dy_(0),
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
    aabb_.move(dx_, dy_);
}

void Entity::setSpeed(int dx, int dy)
{
    dx_ = dx;
    dy_ = dy;
}

float Entity::getMaxVelocity() const
{
    return maxVelocity_;
}
