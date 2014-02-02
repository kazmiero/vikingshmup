#include "Obstacle.h"

Obstacle::Obstacle() : Element()
{
    //ctor
}

Obstacle::Obstacle(const AABB& aabb, const std::string &spriteName) : Element(aabb, spriteName)
{
}

Obstacle::~Obstacle()
{
    //dtor
}

void Obstacle::move()
{
    // do nothing !
}
