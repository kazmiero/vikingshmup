#include "Trajectory.h"
#include "ProgramConstants.h"

#include <iostream>
#include <cmath>

#define PI 3.14159265

Trajectory::Trajectory(Vector2f initialSpeed) :
    initialSpeed_(initialSpeed),
    periodic_(false),
    currentFrame_(0)
{

}

Trajectory::~Trajectory()
{
    //dtor
}

void Trajectory::initUniformAcceleratedTrajectory(float acceleration, float duration /*= 2.0f*/)
{
    float fps = ProgramConstants::getInstance().getFps();
    /// per frame acceleration
    float frameAcc = acceleration / (fps*fps);
    Vector2f ori = initialSpeed_;
    ori.normalize();

    /// compute 2s of movement
    for (Uint32 t = 0; t < duration*fps; t++)
    {
        float speed = t * frameAcc;
        speed_.push_back(initialSpeed_ + ori*speed);
    }
}

void Trajectory::initSinusoidalTrajectory(float period, float amplitude)
{
    float fps = ProgramConstants::getInstance().getFps();

    Vector2f ori = initialSpeed_;
    ori.normalize();

    Vector2f ortho = Vector2f::getOrthogonalVector(ori);

    float norm = initialSpeed_.norm();

    for (Uint32 t = 0; t < period*fps; t++)
    {
        float deriv = cosf(2*PI*t/(fps*period)) * amplitude/(fps*period);
        Vector2f dir = ori + ortho*deriv;
        dir.normalize();

        speed_.push_back(dir*norm);
    }

    periodic_ = true;
}

const Vector2f& Trajectory::getCurrentSpeed() const
{
    return speed_[currentFrame_];
}

void Trajectory::update()
{
    currentFrame_++;

    if (currentFrame_ == speed_.size())
    {
        if (periodic_)
            currentFrame_ = 0;
        else
            currentFrame_--;
    }
}

void Trajectory::bounce(const Vector2f& normal, const Vector2f& tangent)
{
    for (Uint32 i = currentFrame_; i < speed_.size(); i++)
        speed_[i].bounce(normal, tangent);

    if (periodic_)
    {
        for (Uint32 j = 0; j < currentFrame_; j++)
            speed_[j].bounce(normal, tangent);
    }
}
