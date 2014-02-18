#include "BulletShooter.h"
#include "ProgramConstants.h"

BulletShooter::BulletShooter(const BulletModel& bulletModel, const float shootCadency, const float bulletSpeed) :
    shootCadency_(shootCadency),
    bulletVelocity_(bulletSpeed),
    bulletModel_(bulletModel)
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
        timer_->start();
        Trajectory traj(ori * bulletVelocity_/ProgramConstants::getInstance().getFps());
        //return new Bullet(bulletModel_, pos, ori, bulletVelocity_);
        return new Bullet(bulletModel_, pos, traj);
    }

    return NULL;
}
