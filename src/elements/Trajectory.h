#ifndef TRAJECTORY_H
#define TRAJECTORY_H

#include "world/Vector2f.h"
#include <vector>

class Trajectory
{
    public:
        Trajectory(Vector2f initialSpeed);
        Trajectory(const Trajectory& other);
        virtual ~Trajectory();

        void initUniformAcceleratedTrajectory(float acceleration, float duration = 2.0f);
        void initSinusoidalTrajectory(float period, float amplitude);

        const Vector2f& getCurrentSpeed() const;
        bool empty() const;

        void update();
        void bounce(const Vector2f& normal, const Vector2f& tangent);
    protected:
        Vector2f initialSpeed_;
        std::vector<Vector2f> speed_;
        bool periodic_;
        Uint32 currentFrame_;

};

#endif // TRAJECTORY_H
