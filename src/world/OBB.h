#ifndef OBB_H
#define OBB_H

#include "Polygon.h"

/// @file OBB.h

/// @class OBB
/// An OBB has only 2 normals, whereas a general 4-point Polygon has 4 normals
class OBB : public Polygon
{
    public:
        OBB(const AABB& aabb);
        OBB(const AABB& rotatedAABB, double angleDegrees);
        virtual ~OBB();

        virtual const Vector2f& getNormal(Uint32 i) const;
    protected:
    private:
        void setNormals(double angleDegrees);
};

#endif // OBB_H
