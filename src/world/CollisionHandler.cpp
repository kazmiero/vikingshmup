#include "CollisionHandler.h"
#include <iostream>

CollisionHandler::CollisionHandler()
{
    //ctor
}

CollisionHandler::~CollisionHandler()
{
    //dtor
}

bool CollisionHandler::isInCamera(const AABB& aabb)
{
    Vector2f upLeftCorner = aabb.getUpLeftCorner();

    return  upLeftCorner.x_ + aabb.getW() >= AABB::camera.getPos().x_
            && upLeftCorner.x_ <= AABB::camera.getPos().x_ + AABB::camera.getW()
            && upLeftCorner.y_ + aabb.getH() >= AABB::camera.getPos().y_
            && upLeftCorner.y_ <= AABB::camera.getPos().y_ + AABB::camera.getH();
}

bool CollisionHandler::cameraCollisionCheck(const AABB& aabb)
{
    Vector2f relativePos = aabb.getUpLeftCorner() - AABB::camera.getPos();

    return  relativePos.x_ < 0
            || relativePos.x_ + aabb.getW() > AABB::camera.getW()
            || relativePos.y_ < 0
            || relativePos.y_ + aabb.getH() > AABB::camera.getH();
}

bool CollisionHandler::twoAABBCollisionCheck(const AABB& aabb1, const AABB& aabb2)
{
    Vector2f upLeftCorner1 = aabb1.getUpLeftCorner();
    Vector2f upLeftCorner2 = aabb2.getUpLeftCorner();

    return !(
             upLeftCorner2.x_ > upLeftCorner1.x_ + aabb1.getW()
             || upLeftCorner2.x_ + aabb2.getW() < upLeftCorner1.x_
             || upLeftCorner2.y_ > upLeftCorner1.y_ + aabb1.getH()
             || upLeftCorner2.y_ + aabb2.getH() < upLeftCorner1.y_
             );
}

bool CollisionHandler::scrollingCollisionCheck(const AABB& aabb)
{
    Vector2f relativePos = aabb.getUpLeftCorner() - AABB::camera.getPos();

    return relativePos.y_ + aabb.getH() >= AABB::camera.getH();
}

bool CollisionHandler::twoPolygonsCollisionCheck(const Polygon& polygon1, const Polygon& polygon2)
{
    for (Uint32 n = 0; n<polygon1.getNormals().size(); n++)
    {
        Vector2f axis = polygon1.getNormals()[n];
        Vector2f proj1 = getProjection(axis, polygon1);
        Vector2f proj2 = getProjection(axis, polygon2);

        if (!overlap(proj1, proj2))
            return false;
    }

    for (Uint32 n = 0; n<polygon2.getNormals().size(); n++)
    {
        Vector2f axis = polygon2.getNormals()[n];
        Vector2f proj1 = getProjection(axis, polygon1);
        Vector2f proj2 = getProjection(axis, polygon2);

        if (!overlap(proj1, proj2))
            return false;
    }

    return true;
}

bool CollisionHandler::pointInPolygonCheck(const Vector2f& point, const Polygon& polygon)
{
    for (Uint32 n = 0; n<polygon.getNormals().size(); n++)
    {
        Vector2f axis = polygon.getNormals()[n];
        Vector2f proj = getProjection(axis, polygon);
        float pointProj = axis.dotProduct(point);

        if (pointProj > std::max(proj.x_, proj.y_) ||pointProj < std::min(proj.x_, proj.y_))
            return false;
    }

    return true;
}


Vector2f CollisionHandler::getProjection(Vector2f& axis, const Polygon& polygon)
{
    float minP = axis.dotProduct(polygon.getVertices()[0]);
    float maxP = minP;

    for (Uint32 v = 1; v<polygon.getVertices().size(); v++)
    {
        float p = axis.dotProduct(polygon.getVertices()[v]);
        if (p < minP)
            minP = p;
        else if (p > maxP)
            maxP = p;
    }

    return Vector2f(minP, maxP);
}

bool CollisionHandler::overlap(const Vector2f& proj1, const Vector2f& proj2)
{
    return !(
             std::max(proj1.x_, proj1.y_) < std::min(proj2.x_, proj2.y_)
             || std::max(proj2.x_, proj2.y_) < std::min(proj1.x_, proj1.y_)
            );
}

Uint32 CollisionHandler::circlePolygonCollisionCheck(const Circle& circle, const Polygon& polygon, Vector2f& normal, Vector2f& tangent)
{
    // quick check with bounding AABB
    if (!twoAABBCollisionCheck(circle.getBoundingAABB(), polygon.getBoundingAABB()))
    {
        return false;
    }

    if (pointInPolygonCheck(circle.getCenter(), polygon))
        return 2;

    Uint32 collisionCount = 0;

    for (Uint32 i = 0; i<polygon.getVertices().size(); i++)
    {
        Uint32 j = (i+1)%polygon.getVertices().size();

        if (circleSegmentCollisionCheck(circle, polygon.getVertices()[i], polygon.getVertices()[j]))
        {
            normal = Vector2f(polygon.getNormal(i));
            tangent = (polygon.getVertices()[j]-polygon.getVertices()[i]);
            collisionCount++;
        }

        if (collisionCount == 2)
            break;
    }

    return collisionCount;
}

bool CollisionHandler::circleSegmentCollisionCheck(const Circle& circle, const Vector2f& segP1, const Vector2f& segP2)
{
    Vector2f proj = Vector2f::getOrthogonalProjection(circle.getCenter(), segP1, segP2);

    if ((proj - circle.getCenter()).norm() > circle.getRadius())
    {
        return false;
    }
    else
    {
        if ((proj-segP1).dotProduct(segP2-segP1) > 0 && (proj-segP1).sqNorm() < (segP2-segP1).sqNorm())
        {
            return true;
        }
        else if ((circle.getCenter()-segP1).norm() < circle.getRadius() || (circle.getCenter()-segP2).norm() < circle.getRadius())
        {
            return true;
        }
    }

    return false;
}
