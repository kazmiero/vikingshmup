#include "BulletShooter.h"

BulletShooter::BulletShooter(const float shootCadency, const float bulletSpeed, const float bulletLifetime, const std::string& spriteName, const AABB& aabb) :
    shootCadency_(shootCadency),
    bulletVelocity_(bulletSpeed),
    bulletLifetime_(bulletLifetime),
    spriteName_(spriteName),
    aabb_(aabb)
{
    timer_ = new Timer(shootCadency_);
}

BulletShooter::~BulletShooter()
{
    delete timer_;
}

Bullet* BulletShooter::shoot(Vector2f pos, Vector2f ori)
{
    if (timer_->hasTicked())
    {
        timer_->reset();
        AABB aabb = aabb_;
        aabb.setPos(pos);
        return new Bullet(aabb,spriteName_,bulletLifetime_, ori, bulletVelocity_);
    }

    return NULL;
}
