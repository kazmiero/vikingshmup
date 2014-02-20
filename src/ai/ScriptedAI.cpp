#include "ScriptedAI.h"
#include <cmath>

#include <iostream>

ScriptedAI::ScriptedAI(const AABB& myAABB, const AABB& playerAABB, bool periodicTrajectory, const FireMode firemode, float moveTrigger, float shootTrigger) :
    myAABB_(myAABB),
    playerAABB_(playerAABB),
    periodicTrajectory_(periodicTrajectory),
    firemode_(firemode),
    distanceToPlayerMoveTrigger_(moveTrigger),
    distanceToPlayerShootTrigger_(shootTrigger)
{
    hasMoved_ = false;
    initTrajectoryPoints();
}

ScriptedAI::~ScriptedAI()
{
    //dtor
}

void ScriptedAI::initTrajectoryPoints()
{
    trajectoryPoints_.push_back(myAABB_.getPos());
    trajectoryPoints_.push_back(trajectoryPoints_.back() + Vector2f(100,0));
    trajectoryPoints_.push_back(trajectoryPoints_.back() + Vector2f(50,100));
}

void ScriptedAI::update()
{
    commands_.clear();

    // check for 'Move' command
    if (!hasMoved_)
    {
        if (fabs(myAABB_.getPos().y_ - playerAABB_.getPos().y_) < distanceToPlayerMoveTrigger_)
        {
            hasMoved_ = true;
            commands_.push_back(Move);
        }
    }

    // check for 'Shoot' command
    if (firemode_ == NearPlayer)
    {
        Vector2f dist = myAABB_.getPos() - playerAABB_.getPos();
        if (fabs(dist.norm()) < distanceToPlayerShootTrigger_)
            commands_.push_back(Shoot);
    }
    else if (firemode_ == KeyPositions)
    {
        float epsilon = 0.5f;

        for (Uint32 p = 0; p < trajectoryPoints_.size(); p++)
        {
            if ((myAABB_.getPos() - trajectoryPoints_[p]).sqNorm() < epsilon)
            {
                commands_.push_back(Shoot);
                break;
            }
        }
    }
}

const std::vector<AICommand>& ScriptedAI::getCommands() const
{
    return commands_;
}

const std::vector<Vector2f>& ScriptedAI::getPoints() const
{
    return trajectoryPoints_;
}
