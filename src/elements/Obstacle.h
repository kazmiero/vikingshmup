#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "Element.h"

/// @file Obstacle

/// @class Obstacle
/// A static obstacle. It has generally some bullet properties
class Obstacle : public Element
{
    public:
        Obstacle();
        Obstacle(const AABB& aabb, const std::string &spriteName);
        virtual ~Obstacle();
    protected:
    private:
};

#endif // OBSTACLE_H
