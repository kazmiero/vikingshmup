#include "Obstacle.h"
#include "world/OBB.h"

Obstacle::Obstacle() : Element()
{
    //ctor
}

Obstacle::Obstacle(const AABB& aabb, const std::string &spriteName, double rotation /*= 0.0*/) :
    Element(aabb, spriteName)
{
    rotation_ = rotation;
    initCollisionModel();
}

Obstacle::Obstacle(const ObstacleModel& model, Vector2f pos, double rotation /*= 0.0*/) :
    Element(model, pos)
 {
     rotation_ = rotation;
     initCollisionModel();
 }

Obstacle::~Obstacle()
{
    delete collisionModel_;
}

void Obstacle::move()
{
    // do nothing !
}

void Obstacle::initCollisionModel()
{
    collisionModel_ = new OBB(aabb_, rotation_);
}
