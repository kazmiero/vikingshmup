#include "AIModel.h"

AIModel::AIModel(const bool periodicTrajectory, const FireMode firemode, const float moveTrigger, const float shootTrigger) :
    periodicTrajectory_(periodicTrajectory),
    firemode_(firemode),
    distanceToPlayerMoveTrigger_(moveTrigger),
    distanceToPlayerShootTrigger_(shootTrigger)
{
    //ctor
}

AIModel::~AIModel()
{
    //dtor
}

void AIModel::initPoints(const std::vector<Vector2f>& points)
{
    points_ = points;
}
