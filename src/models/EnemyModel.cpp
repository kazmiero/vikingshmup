#include "EnemyModel.h"

EnemyModel::EnemyModel(const std::string& spriteName, const AABB& aabb, const float maxVelocity, const PatternModel& patternModel) :
    ElementModel(spriteName, aabb),
    maxVelocity_(maxVelocity),
    patternModel_(patternModel)
{
    //ctor
}

EnemyModel::~EnemyModel()
{
    //dtor
}
