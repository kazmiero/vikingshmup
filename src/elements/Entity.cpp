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
