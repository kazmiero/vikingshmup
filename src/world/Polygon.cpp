#include "Polygon.h"

Polygon::Polygon()
{
    // nothing
}

Polygon::Polygon(const std::vector<Vector2f>& vertices)
{
    if (vertices.size()>2)
        vertices_ = vertices;

    computeNormals();
    computeBoundingAABB();
}

Polygon::~Polygon()
{
    //dtor
}

void Polygon::computeNormals()
{
    for (Uint32 i = 0; i < vertices_.size(); i++)
    {
        Uint32 j = (i+1) % vertices_.size();

        Vector2f vec = vertices_[j] - vertices_[i];
        normals_.push_back(Vector2f::getOrthogonalVector(vec));
    }
}

void Polygon::computeBoundingAABB()
{
    float minX = vertices_[0].x_, maxX = vertices_[0].x_, minY = vertices_[0].y_, maxY = vertices_[0].y_;

    for (Uint32 i = 1; i < vertices_.size(); i++)
    {
        if (vertices_[i].x_ < minX)
            minX = vertices_[i].x_;
        if (vertices_[i].x_ > maxX)
            maxX = vertices_[i].x_;
        if (vertices_[i].y_ < minY)
            minY = vertices_[i].y_;
        if (vertices_[i].y_ > maxY)
            maxY = vertices_[i].y_;
    }

    float w = maxX - minX;
    float h = maxY - minY;
    Vector2f pos = Vector2f(maxX + minX, maxY + minY)*0.5f;

    boundingAABB_ = AABB(pos,w,h);
}

const std::vector<Vector2f>& Polygon::getVertices() const
{
    return vertices_;
}

const std::vector<Vector2f>& Polygon::getNormals() const
{
    return normals_;
}

const Vector2f& Polygon::getNormal(Uint32 i) const
{
    return normals_[i];
}

void Polygon::move(Vector2f dp)
{
    for (Uint32 i = 0; i < vertices_.size(); i++)
        vertices_[i] += dp;

    boundingAABB_.move(dp);
}

const AABB& Polygon::getBoundingAABB() const
{
    return boundingAABB_;
}
