#ifndef BULLETSHOOTER_H
#define BULLETSHOOTER_H

#include "Bullet.h"
#include "time/Timer.h"

class BulletShooter
{
    public:
        BulletShooter(const float shootCadency, const float bulletSpeed, const float bulletLifetime, const std::string& spriteName, const AABB& aabb);
        virtual ~BulletShooter();

        Bullet* shoot(Vector2f pos, Vector2f ori);
    protected:
    private:
        const float shootCadency_;        ///< shoots per second
        const float bulletVelocity_;         ///< pixels per second
        const float bulletLifetime_;      ///< seconds
        std::string spriteName_;
        AABB aabb_;

        Timer* timer_;
};

#endif // BULLETSHOOTER_H
