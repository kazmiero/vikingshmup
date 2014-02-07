#include "BulletModel.h"

BulletModel::BulletModel(const std::string& spriteName, const AABB& aabb, const float lifetime) :
    ElementModel(spriteName, aabb),
    lifetime_(lifetime)
{
    //ctor
}

BulletModel::~BulletModel()
{
    //dtor
}
