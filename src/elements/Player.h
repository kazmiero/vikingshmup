#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

/// @file Player.h

/// @class Player
/// The player of the game. Love and friendship always win!
class Player : public Entity
{
    public:
        Player(const AABB& aabb, const std::string& spriteName, float maxVelocity);
        virtual ~Player();

        void back();
    protected:
    private:
};

#endif // PLAYER_H
