#include "PolygonalLine.h"
#include <iostream>

PolygonalLine::PolygonalLine() :
    Trajectory(Vector2f())
{
    //ctor
}

PolygonalLine::~PolygonalLine()
{
    //dtor
}

void PolygonalLine::init(const std::vector<Vector2f>& points, float speed, bool closedCurve)
{
    periodic_ = closedCurve;

    float frameSpeed = speed/ProgramConstants::getInstance().getFps();

    Uint32 iterations = points.size();
    if (!periodic_)
        iterations--;

    for (Uint32 i = 0; i < iterations; i++)
    {
        Vector2f dir = points[(i+1)%points.size()] - points[i];
        float distance = dir.norm();
        dir.normalize();

        Uint32 nbFrame = (Uint32) distance/frameSpeed;
        float lastFrameSpeed = distance - frameSpeed*nbFrame;

        for (Uint32 i = 0; i < nbFrame; i++)
        {
            speed_.push_back(dir*frameSpeed);
        }
        speed_.push_back(dir*lastFrameSpeed);
    }
}
