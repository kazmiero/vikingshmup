#include "ModelManager.h"

ModelManager* ModelManager::instance_ = NULL;

ModelManager& ModelManager::getInstance()
{
    if (instance_ == NULL)
        instance_ = new ModelManager();

    return *instance_;
}

ModelManager::ModelManager()
{
    //ctor
}

ModelManager::~ModelManager()
{
    //dtor
}

const BulletModel& ModelManager::getBulletModelByName(const std::string& name)
{
    return *bulletModels_.at(name);
}

const ObstacleModel& ModelManager::getObstacleModelByName(const std::string& name)
{
    return *obstacleModels_.at(name);
}

void ModelManager::createModels(std::map<std::string,AABB> spritesAABB)
{
    obstacleModels_["default"] = new ObstacleModel("obstacle", spritesAABB["obstacle"]);

    bulletModels_["default"] = new BulletModel("bullet", spritesAABB["bullet"], 3.0f);
}
