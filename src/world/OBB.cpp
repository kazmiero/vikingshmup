#include "OBB.h"
#include <cmath>

#define PI 3.14159265

OBB::OBB(const AABB& aabb)
{
    vertices_.push_back(aabb.getUpLeftCorner());
    vertices_.push_back(aabb.getPos() + Vector2f(aabb.getW()/2, -aabb.getH()/2));   // up right
    vertices_.push_back(aabb.getPos() + Vector2f(aabb.getW()/2, aabb.getH()/2));    // down right
    vertices_.push_back(aabb.getPos() + Vector2f(-aabb.getW()/2, aabb.getH()/2));   // down left

    setNormals(0.0);
}

OBB::OBB(const AABB& rotatedAABB, double angleDegrees)
{
    vertices_.push_back(rotatedAABB.getUpLeftCorner());
    vertices_.push_back(rotatedAABB.getPos() + Vector2f(rotatedAABB.getW()/2, -rotatedAABB.getH()/2));   // up right
    vertices_.push_back(rotatedAABB.getPos() + Vector2f(rotatedAABB.getW()/2, rotatedAABB.getH()/2));    // down right
    vertices_.push_back(rotatedAABB.getPos() + Vector2f(-rotatedAABB.getW()/2, rotatedAABB.getH()/2));   // down left

    for (Uint32 i = 0; i < 4; i++)
        vertices_[i].applyRotation(rotatedAABB.getPos(), -angleDegrees);

    computeNormals();
    normals_.pop_back();
    normals_.pop_back();
    //setNormals(-angleDegrees);
}

OBB::~OBB()
{
    //dtor
}

void OBB::setNormals(double angleDegrees)
{
    double angleRadians = angleDegrees * PI / 180.0;

    normals_.push_back(Vector2f(-sin(angleRadians), cos(angleRadians)));
    normals_.push_back(Vector2f(cos(angleRadians), sin(angleRadians)));
}

const Vector2f& OBB::getNormal(Uint32 i) const
{
    return normals_[i % 2];
}
