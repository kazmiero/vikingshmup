#ifndef COLLISIONMODEL_H
#define COLLISIONMODEL_H

#include "AABB.h"

/// @file CollisionModel.h

/// @class CollisionModel
/// abstract class describing a collision model other than the AABB
class CollisionModel
{
    public:
        CollisionModel();
        virtual ~CollisionModel();
        virtual void move(Vector2f dp) = 0;
        virtual const AABB& getBoundingAABB() const = 0;
    private:
};

#endif // COLLISIONMODEL_H
