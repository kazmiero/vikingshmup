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
    return  aabb.getPos().x_ + aabb.getW() >= AABB::camera.getPos().x_
            && aabb.getPos().x_ <= AABB::camera.getPos().x_ + AABB::camera.getW()
            && aabb.getPos().y_ + aabb.getH() >= AABB::camera.getPos().y_
            && aabb.getPos().y_ <= AABB::camera.getPos().y_ + AABB::camera.getH();
}

bool CollisionHandler::cameraCollisionCheck(const AABB& aabb)
{
    Vector2f relativePos = aabb.getPos() - AABB::camera.getPos();

    return  relativePos.x_ < 0
            || relativePos.x_ + aabb.getW() > AABB::camera.getW()
            || relativePos.y_ < 0
            || relativePos.y_ + aabb.getH() > AABB::camera.getH();
}

bool CollisionHandler::twoAABBCollisionCheck(const AABB& aabb1, const AABB& aabb2)
{
    return !(
             aabb2.getPos().x_ > aabb1.getPos().x_ + aabb1.getW()
             || aabb2.getPos().x_ + aabb2.getW() < aabb1.getPos().x_
             || aabb2.getPos().y_ > aabb1.getPos().y_ + aabb1.getH()
             || aabb2.getPos().y_ + aabb2.getH() < aabb1.getPos().y_
             );
}
