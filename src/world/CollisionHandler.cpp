#include "CollisionHandler.h"

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
