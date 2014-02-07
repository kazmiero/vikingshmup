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
