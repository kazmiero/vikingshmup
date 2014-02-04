#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

#include "AABB.h"

class CollisionHandler
{
    public:
        CollisionHandler();
        virtual ~CollisionHandler();

        /// collision between 2 elements given their AABBs
        bool twoAABBCollisionCheck(const AABB& aabb1, const AABB& aabb2);
        ///
        bool isInCamera(const AABB& aabb);
        bool cameraCollisionCheck(const AABB& aabb);

    private:
};

#endif // COLLISIONHANDLER_H
