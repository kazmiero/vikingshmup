#include "Player.h"

Player::Player(const AABB& aabb, const std::string& spriteName, float maxVelocity) :
    Entity(aabb, spriteName, maxVelocity)
{
    //ctor
}

Player::~Player()
{
    //dtor
}

void Player::back()
{
    aabb_.move(dp_*-1.0f);
}

void Player::scroll(Vector2f cameraScrolling)
{
    aabb_.move(cameraScrolling);
}
