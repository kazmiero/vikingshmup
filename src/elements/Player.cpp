#include "Player.h"
#include <iostream>

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
    relativeCannonRotationCenter_ = Vector2f(0.0f, cannonAABB_.getH());
    cannonOrientation_ = 0.0;
    cannonAABB_.move(Vector2f(0.0f, -cannonAABB_.getH()/2));
}

Player::~Player()
{
    //dtor
}

void Player::initShooter(const BulletModel& bulletModel)
{
    bulletShooter_ = new BulletShooter(bulletModel, 10.0f, 240.0f);
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

Bullet* Player::shoot()
{
    Vector2f ori = Vector2f::getOrientationByAngle(cannonOrientation_);
    Vector2f pos = aabb_.getPos() + ori * aabb_.getH();

    return bulletShooter_->shoot(pos, ori);
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
    return relativeCannonRotationCenter_.toSDL_Point();
}

const double Player::getCannonOrientation() const
{
    return cannonOrientation_;
}
