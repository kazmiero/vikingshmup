#include "AIEnemy.h"
#include "PolygonalLine.h"

AIEnemy::AIEnemy(const EnemyModel& model, Vector2f pos) :
    Enemy(model, pos),
    autofire_(false),
    shootingOnePattern_(false)
{
    trajectory_ = NULL;
}

AIEnemy::~AIEnemy()
{
    if (trajectory_ != NULL)
        delete trajectory_;
}

const Uint32 AIEnemy::getAiId() const
{
    return aiId_;
}

void AIEnemy::setAiId(Uint32 id)
{
    aiId_ = id;
}

void AIEnemy::initTrajectory(const std::vector<Vector2f>& points, bool periodicTrajectory)
{
    trajectory_ = new PolygonalLine();
    dynamic_cast<PolygonalLine*>(trajectory_)->init(points, maxVelocity_, periodicTrajectory, 1.0f);
}

bool AIEnemy::hasAI() const
{
    return true;
}

bool AIEnemy::isShooting() const
{
    return shootingOnePattern_;
}

void AIEnemy::setShooting(bool shooting)
{
    shootingOnePattern_ = shooting;
}

bool AIEnemy::autofire() const
{
    return autofire_;
}

void AIEnemy::setAutofire(bool autofire)
{
    autofire_ = autofire;
}

void AIEnemy::move()
{
    if (trajectory_ != NULL)
    {
       dp_ = trajectory_->getCurrentSpeed();
       trajectory_->update();
    }

    aabb_.move(dp_);
}

std::vector<Bullet*>* AIEnemy::shootPattern()
{
    Vector2f ori = Vector2f();

    if (aimAtPlayer_)
    {
        ori = player_->getAABB().getPos() - aabb_.getPos();
        ori.normalize();
    }

    if (autofire_)
        return patternShooter_->shoot(aabb_.getPos(), ori);
    else if (shootingOnePattern_)
        return patternShooter_->shootOnePattern(aabb_.getPos(), shootingOnePattern_, ori);
    else
        return NULL;
}
