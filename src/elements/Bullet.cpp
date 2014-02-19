#include "Bullet.h"
#include "ProgramConstants.h"
#include "world/Circle.h"
#include <iostream>

#include "PolygonalLine.h"

Bullet::Bullet(const AABB& aabb, const std::string& spriteName, float lifetime, Vector2f ori, float velocity) :
    Element(aabb, spriteName)
{
    // calculate frame number lifetime_ with second lifetime
    lifetime_ = int(lifetime*ProgramConstants::getInstance().getFps());

    // calculate dp_
    dp_ = ori * velocity/ProgramConstants::getInstance().getFps();

    initCollisionModel();

    trajectory_ = NULL;

    lastBounce_ = lifetime_+2;
}

Bullet::Bullet(const BulletModel& model, Vector2f pos, Vector2f ori, float velocity) :
    Element(model, pos)
{
    // calculate frame number lifetime_ with second lifetime
    lifetime_ = int(model.lifetime_*ProgramConstants::getInstance().getFps());

    // calculate dp_
    dp_ = ori * velocity/ProgramConstants::getInstance().getFps();

    initCollisionModel();

    trajectory_ = NULL;

    lastBounce_ = lifetime_+2;
}

Bullet::Bullet(const BulletModel& model, Vector2f pos, const Trajectory& trajectory) :
    Element(model, pos)
{
    // calculate frame number lifetime_ with second lifetime
    lifetime_ = int(model.lifetime_*ProgramConstants::getInstance().getFps());

    initCollisionModel();

    trajectory_ = NULL;

    setTrajectory(trajectory);

    lastBounce_ = lifetime_+2;
}

Bullet::~Bullet()
{
    delete collisionModel_;

    if (trajectory_ != NULL)
        delete trajectory_;
}

void Bullet::move()
{
    if (trajectory_ != NULL)
    {
       dp_ = trajectory_->getCurrentSpeed();
       trajectory_->update();
    }

    aabb_.move(dp_);
    collisionModel_->move(dp_);
    lifetime_--;
}

void Bullet::bounce(const Vector2f& normal, const Vector2f& tangent)
{
    if (lastBounce_ - lifetime_ <= 1)
        return;

    if (trajectory_ != NULL)
    {
        trajectory_->bounce(normal, tangent);
        lastBounce_ = lifetime_;
    }
    else
    {
        dp_.bounce(normal, tangent);
        lastBounce_ = lifetime_;
    }
}

bool Bullet::lives()
{
    return lifetime_>0;
}

void Bullet::initCollisionModel()
{
    collisionModel_ = new Circle(aabb_);
}

void Bullet::initTrajectory()
{
//    std::vector<Vector2f> points;
//    points.push_back(aabb_.getPos());
//    points.push_back(points.back() + Vector2f(0, -100));
//    points.push_back(points.back() + Vector2f(100, 0));
//    points.push_back(points.back() + Vector2f(-20, 80));
//    points.push_back(points.back() + Vector2f(-150, -50));
//
//    trajectory_ = new PolygonalLine();
//    dynamic_cast<PolygonalLine*>(trajectory_)->init(points, 600.0f, true);


    trajectory_ = new Trajectory(dp_);
    //trajectory_->initUniformAcceleratedTrajectory(100.0);
    trajectory_->initSinusoidalTrajectory(0.5f, 40.0f);
}

void Bullet::setTrajectory(const Trajectory& trajectory)
{
    // uniform speed
    if (trajectory.empty())
    {
        dp_ = trajectory.getCurrentSpeed();

        // destroy current trajectory
        if (trajectory_ != NULL)
            delete trajectory_;
    }
    else
    {
        trajectory_ = new Trajectory(trajectory);
    }
}
