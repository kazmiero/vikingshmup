#include "Player.h"

Player::Player(const AABB& aabb, const std::string& spriteName, float maxVelocity) :
    Entity(aabb, spriteName, maxVelocity)
{
    //ctor
}

Player::Player(const AABB& aabb, const std::string& spriteName, float maxVelocity, const AABB& cannonAABB, const std::string& cannonSpriteName) :
    Entity(aabb, spriteName, maxVelocity),
    cannonAABB_(cannonAABB),
    cannonSpriteName_(cannonSpriteName)
{
    relativeCannonRotationCenter_ = Vector2f(cannonAABB_.getW()/2, cannonAABB_.getH());
    cannonOrientation_ = 0.0;
    cannonAABB_.move(Vector2f(aabb_.getW()/2 - cannonAABB_.getW()/2, 0.0f));
}

Player::~Player()
{
    //dtor
}

void Player::move()
{
    aabb_.move(dp_);
    cannonAABB_.move(dp_);
}

void Player::back()
{
    aabb_.move(dp_*-1.0f);
    cannonAABB_.move(dp_*-1.0f);
}

void Player::scroll(Vector2f cameraScrolling)
{
    aabb_.move(cameraScrolling);
    cannonAABB_.move(cameraScrolling);
}

void Player::changeOrientation(bool positive)
{
    if (positive)
        cannonOrientation_ += 10.0;
    else
        cannonOrientation_ -= 10.0;

    if (cannonOrientation_ > 90.0)
        cannonOrientation_ = 90.0;
    else if (cannonOrientation_ < -90.0)
        cannonOrientation_ = -90.0;

}

const AABB& Player::getCannonAABB() const
{
    return cannonAABB_;
}

const std::string& Player::getCannonSpriteName() const
{
    return cannonSpriteName_;
}

const SDL_Point Player::getRotationCenter() const
{
    //Vector2f center = aabb_.getPos() + relativeCannonRotationCenter_ - AABB::camera.getPos();
    return relativeCannonRotationCenter_.toSDL_Point();
}

const double Player::getCannonOrientation() const
{
    return cannonOrientation_;
}
