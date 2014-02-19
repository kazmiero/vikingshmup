#ifndef POLYGONALLINE_H
#define POLYGONALLINE_H

#include "Trajectory.h"
#include "ProgramConstants.h"

/// @file PolygonalLine.h

/// @class PolygonalLine
/// Polygonal line (or 1-Spline) trajectory with constant speed
class PolygonalLine : public Trajectory
{
    public:
        PolygonalLine();
        virtual ~PolygonalLine();

        void init(const std::vector<Vector2f>& points, float speed, bool closedCurve);
    protected:
    private:
};

#endif // POLYGONALLINE_H
