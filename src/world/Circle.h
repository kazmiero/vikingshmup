#ifndef CIRCLE_H
#define CIRCLE_H

#include "CollisionModel.h"

class Circle : public CollisionModel
{
    public:
        Circle();
        Circle(const Vector2f& center, float radius);
        Circle(const AABB& aabb);
        virtual ~Circle();

        const Vector2f& getCenter() const;
        float getRadius() const;
        virtual void move(Vector2f dp);
        virtual const AABB& getBoundingAABB() const;
    private:
        Vector2f center_;
        float radius_;
        AABB boundingAABB_;
};

#endif // CIRCLE_H
