#ifndef CIRCLE_H
#define CIRCLE_H

#include "AABB.h"

class Circle
{
    public:
        Circle();
        Circle(const Vector2f& center, float radius);
        Circle(const AABB& aabb);
        virtual ~Circle();

        const Vector2f& getCenter() const;
        float getRadius() const;
    protected:
    private:
        Vector2f center_;
        float radius_;
};

#endif // CIRCLE_H
