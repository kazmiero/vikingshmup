#include "ElementModel.h"

ElementModel::ElementModel(const std::string& spriteName, const AABB& aabb) :
    spriteName_(spriteName),
    aabb_(aabb)
{
    //ctor
}

ElementModel::~ElementModel()
{
    //dtor
}
