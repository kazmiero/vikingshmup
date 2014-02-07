#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "Element.h"
#include "models/ObstacleModel.h"

/// @file Obstacle

/// @class Obstacle
/// A static obstacle. It has generally some bullet properties
class Obstacle : public Element
{
    public:
        Obstacle();
        Obstacle(const AABB& aabb, const std::string &spriteName);
        Obstacle(const ObstacleModel& model, Vector2f pos);
        virtual ~Obstacle();

        virtual void move();
    protected:
    private:
};

#endif // OBSTACLE_H
