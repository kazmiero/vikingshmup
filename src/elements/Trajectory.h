#ifndef TRAJECTORY_H
#define TRAJECTORY_H

#include "world/Vector2f.h"
#include <vector>

class Trajectory
{
    public:
        Trajectory(Vector2f initialSpeed);
        virtual ~Trajectory();

        void initUniformAcceleratedTrajectory(float acceleration, float duration = 2.0f);

        const Vector2f& getCurrentSpeed() const;
        void update();

        void bounce(const Vector2f& normal, const Vector2f& tangent);
    protected:
    private:
        Vector2f initialSpeed_;
        std::vector<Vector2f> speed_;
        bool periodic_;
        Uint32 currentFrame_;

};

#endif // TRAJECTORY_H
