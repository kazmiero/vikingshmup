#ifndef POLYGON_H
#define POLYGON_H

#include "CollisionModel.h"
#include <vector>

/// @file Polygon.h

/// @class Polygon
/// Convex polygon representation for collision detection
class Polygon : public CollisionModel
{
    public:
        Polygon();
        Polygon(const std::vector<Vector2f>& vertices);

        virtual ~Polygon();

        const std::vector<Vector2f>& getVertices() const;
        const std::vector<Vector2f>& getNormals() const;
        virtual const Vector2f& getNormal(Uint32 i) const;

        virtual void move(Vector2f dp);
        virtual const AABB& getBoundingAABB() const;

    protected:
        void computeBoundingAABB();
        void computeNormals();

        std::vector<Vector2f> vertices_;
        std::vector<Vector2f> normals_;
        AABB boundingAABB_;
};

#endif // POLYGON_H
