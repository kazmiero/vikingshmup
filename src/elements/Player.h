#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "BulletShooter.h"

/// @file Player.h

/// @class Player
/// The player of the game. Love and friendship always win!
class Player : public Entity
{
    public:
        Player(const AABB& aabb, const std::string& spriteName, float maxVelocity);
        Player(const AABB& aabb, const std::string& spriteName, float maxVelocity, const AABB& cannonAABB, const std::string& cannonSpriteName);
        virtual ~Player();

        void initShooter(const BulletModel& bulletModel);

        virtual void move();
        void back();
        void scroll(Vector2f cameraScrolling);

        void changeOrientation(bool positive);
        Bullet* shoot();

        const AABB& getCannonAABB() const;
        const SDL_Point getRotationCenter() const;
        const double getCannonOrientation() const;
        const std::string& getCannonSpriteName() const;
    protected:
    private:
        /// triangle collision model (!!! specific to the actual sprite)
        void initCollisionModel();

        AABB cannonAABB_;
        std::string cannonSpriteName_;
        Vector2f relativeCannonRotationCenter_;
        double cannonOrientation_;

        BulletShooter* bulletShooter_;
};

#endif // PLAYER_H
