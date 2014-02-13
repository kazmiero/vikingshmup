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
        Obstacle(const AABB& aabb, const std::string &spriteName, double rotation = 0.0);
        Obstacle(const ObstacleModel& model, Vector2f pos, double rotation = 0.0);
        virtual ~Obstacle();

        virtual void move();
    protected:
    private:
        /// our basic obstacle has an OBB Collision Model
        void initCollisionModel();
};

#endif // OBSTACLE_H
