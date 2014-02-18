#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

#include "Polygon.h"
#include "Circle.h"

class CollisionHandler
{
    public:
        CollisionHandler();
        virtual ~CollisionHandler();

        /// collision between 2 elements given their AABBs
        bool twoAABBCollisionCheck(const AABB& aabb1, const AABB& aabb2);
        /// collision between 2 convex polygons using the SAT method
        bool twoPolygonsCollisionCheck(const Polygon& polygon1, const Polygon& polygon2);
        /// collision between a circle and a convex polygon, return the collision normal
        /// @return 0 if no collision, 1 for edge collision, 2 for corner collision
        Uint32 circlePolygonCollisionCheck(const Circle& circle, const Polygon& polygon, Vector2f& normal, Vector2f& tangent);
        /// intersection between point and polygon
        bool pointInPolygonCheck(const Vector2f& point, const Polygon& polygon);


        bool isInCamera(const AABB& aabb);
        bool cameraCollisionCheck(const AABB& aabb);
        bool scrollingCollisionCheck(const AABB& aabb);

    private:
        /// used for the SAT test
        Vector2f getProjection(Vector2f& axis, const Polygon& polygon);
        bool overlap(const Vector2f& proj1, const Vector2f& proj2);

        /// used for circle polygon collision
        bool circleSegmentCollisionCheck(const Circle& circle, const Vector2f& segP1, const Vector2f& segP2);
};

#endif // COLLISIONHANDLER_H
