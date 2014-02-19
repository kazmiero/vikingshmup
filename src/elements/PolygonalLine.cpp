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

void PolygonalLine::init(const std::vector<Vector2f>& points, float speed, bool closedCurve, float delay /*= 0.0f*/)
{
    periodic_ = closedCurve;

    float frameSpeed = speed/ProgramConstants::getInstance().getFps();

    Uint32 frameDelay = 0;
    if (delay > 0.0f)
    {
        frameDelay = (Uint32) (delay * ProgramConstants::getInstance().getFps());
    }

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

        // wait for frameDelay frames
        for (Uint32 d = 0; d < frameDelay; d++)
        {
            speed_.push_back(Vector2f());
        }

        speed_.push_back(dir*lastFrameSpeed);
    }
}
