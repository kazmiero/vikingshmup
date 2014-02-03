#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

#include "AABB.h"

class CollisionHandler
{
    public:
        CollisionHandler(const AABB& cameraAABB);
        virtual ~CollisionHandler();

        /// collision between 2 elements given their AABBs
        bool twoAABBCollisionCheck(const AABB& aabb1, const AABB& aabb2);
        ///
        bool isInCamera(const AABB& aabb);
        bool cameraCollisionCheck(const AABB& aabb);

        void setCameraAABB(const AABB& cameraAABB);

    private:
        AABB cameraAABB_;
};

#endif // COLLISIONHANDLER_H
