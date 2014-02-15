#include "EnemyModel.h"

EnemyModel::EnemyModel(const std::string& spriteName, const AABB& aabb, const BulletModel& bulletModel) :
    ElementModel(spriteName, aabb),
    bulletModel_(bulletModel)
{
    //ctor
}

EnemyModel::~EnemyModel()
{
    //dtor
}
