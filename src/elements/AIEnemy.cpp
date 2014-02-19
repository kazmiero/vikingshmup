#include "AIEnemy.h"
#include "PolygonalLine.h"

AIEnemy::AIEnemy(const EnemyModel& model, Vector2f pos) :
    Enemy(model, pos)
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

void AIEnemy::initTrajectory(const std::vector<Vector2f>& points)
{
    trajectory_ = new PolygonalLine();
    dynamic_cast<PolygonalLine*>(trajectory_)->init(points, maxVelocity_, true, 1.0f);
}

bool AIEnemy::hasAI() const
{
    return true;
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
