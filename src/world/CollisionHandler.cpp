#include "CollisionHandler.h"

CollisionHandler::CollisionHandler(const AABB& cameraAABB) :
    cameraAABB_(cameraAABB)
{
    //ctor
}

CollisionHandler::~CollisionHandler()
{
    //dtor
}

bool CollisionHandler::isInCamera(const AABB& aabb)
{
    return  aabb.getPos().x_ + aabb.getW() >= cameraAABB_.getPos().x_
            && aabb.getPos().x_ <= cameraAABB_.getPos().x_ + cameraAABB_.getW()
            && aabb.getPos().y_ + aabb.getH() >= cameraAABB_.getPos().y_
            && aabb.getPos().y_ <= cameraAABB_.getPos().y_ + cameraAABB_.getH();
}

bool CollisionHandler::cameraCollisionCheck(const AABB& aabb)
{
    Vector2f relativePos = aabb.getPos() - cameraAABB_.getPos();

    return  relativePos.x_ < 0
            || relativePos.x_ + aabb.getW() > cameraAABB_.getW()
            || relativePos.y_ < 0
            || relativePos.y_ + aabb.getH() > cameraAABB_.getH();
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

void CollisionHandler::setCameraAABB(const AABB& cameraAABB)
{
    cameraAABB_ = cameraAABB;
}
