#ifndef ENEMY_H
#define ENEMY_H

#include "Player.h"
#include "BulletShooter.h"
#include "models/EnemyModel.h"


class Enemy : public Entity
{
    public:
        Enemy();
        Enemy(const AABB& aabb, const std::string& spriteName, float maxVelocity);
        Enemy(const EnemyModel& model, Vector2f pos);
        virtual ~Enemy();

        void initShooter(const BulletModel& bulletModel);
        Bullet* shoot();
        Bullet* shootToPlayer();

        /// @return true if dead
        bool injure();

        void setPlayer(const Player* player);
    protected:
    private:
        BulletShooter* bulletShooter_;
        Uint32 hp_;
        const Player* player_;
};

#endif // ENEMY_H
