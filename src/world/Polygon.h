#ifndef POLYGON_H
#define POLYGON_H

#include "AABB.h"
#include <vector>

/// @file Polygon.h

/// @class Polygon
/// Convex polygon representation for collision detection
class Polygon
{
    public:
        Polygon();
        Polygon(const std::vector<Vector2f>& vertices);

        virtual ~Polygon();

        const std::vector<Vector2f>& getVertices() const;
        const std::vector<Vector2f>& getNormals() const;
        virtual const Vector2f& getNormal(Uint32 i) const;

        AABB computeBoundingAABB();

    protected:
        void computeNormals();

        std::vector<Vector2f> vertices_;
        std::vector<Vector2f> normals_;
};

#endif // POLYGON_H
