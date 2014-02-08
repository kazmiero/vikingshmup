#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

#include "Polygon.h"

class CollisionHandler
{
    public:
        CollisionHandler();
        virtual ~CollisionHandler();

        /// collision between 2 elements given their AABBs
        bool twoAABBCollisionCheck(const AABB& aabb1, const AABB& aabb2);
        /// collision between 2 convex polygons using the SAT method
        bool twoPolygonsCollisionCheck(const Polygon& polygon1, const Polygon& polygon2);

        bool isInCamera(const AABB& aabb);
        bool cameraCollisionCheck(const AABB& aabb);
        bool scrollingCollisionCheck(const AABB& aabb);

    private:
        /// used for the SAT test
        Vector2f getProjection(Vector2f& axis, const Polygon& polygon);
        bool overlap(const Vector2f& proj1, const Vector2f& proj2);
};

#endif // COLLISIONHANDLER_H
