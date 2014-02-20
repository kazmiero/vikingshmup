#include "EnemyModel.h"

EnemyModel::EnemyModel(const std::string& spriteName, const AABB& aabb, const BulletModel& bulletModel, const PatternModel& patternModel) :
    ElementModel(spriteName, aabb),
    bulletModel_(bulletModel),
    patternModel_(patternModel)
{
    //ctor
}

EnemyModel::~EnemyModel()
{
    //dtor
}
