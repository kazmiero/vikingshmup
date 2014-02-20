#ifndef ENEMY_H
#define ENEMY_H

#include "Player.h"
#include "BulletShooter.h"
#include "PatternShooter.h"
#include "models/EnemyModel.h"


class Enemy : public Entity
{
    public:
        Enemy(const AABB& aabb, const std::string& spriteName, float maxVelocity);
        Enemy(const EnemyModel& model, Vector2f pos);
        virtual ~Enemy();

        void initShooter(const BulletModel& bulletModel);
        Bullet* shoot();
        virtual std::vector<Bullet*>* shootPattern();

        /// @return true if dead
        bool injure();
        bool invisible();

        bool patternShoot() const;
        void setPlayer(const Player* player);

        virtual bool hasAI() const;
    protected:
        const Player* player_;
        bool patternShoot_;
        bool aimAtPlayer_;
        BulletShooter* bulletShooter_;
        PatternShooter* patternShooter_;

    private:
        Uint32 hp_;

        /// timer for invisibility frames
        Timer* animationTimer_;
};

#endif // ENEMY_H
