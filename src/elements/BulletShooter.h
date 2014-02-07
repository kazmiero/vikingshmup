#ifndef BULLETSHOOTER_H
#define BULLETSHOOTER_H

#include "Bullet.h"
#include "time/Timer.h"
#include "models/BulletModel.h"

class BulletShooter
{
    public:
        BulletShooter(const BulletModel& bulletModel, const float shootCadency, const float bulletSpeed);
        virtual ~BulletShooter();

        Bullet* shoot(Vector2f pos, Vector2f ori);
    protected:
    private:
        const float shootCadency_;        ///< shoots per second
        const float bulletVelocity_;         ///< pixels per second

        const BulletModel& bulletModel_;

        Timer* timer_;
};

#endif // BULLETSHOOTER_H
