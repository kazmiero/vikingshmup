#ifndef ENTITY_H
#define ENTITY_H

#include "Element.h"

/// @file Entity.h

/// @class Entity
/// A vessel in our shmup world. Can be the player or an enemy. It has a velocity
class Entity : public Element
{
    public:
        Entity();
        Entity(const AABB& aabb, const std::string &spriteName, float maxVelocity);
        virtual ~Entity();
    protected:
        int dx_, dy_;
        float velocity_;        // pixels per second
        float maxVelocity_;     // pixels per second
    private:
};

#endif // ENTITY_H
