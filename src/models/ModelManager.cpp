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

const EnemyModel& ModelManager::getEnemyModelByName(const std::string& name)
{
    return *enemyModels_.at(name);
}

const PatternModel& ModelManager::getPatternModelByName(const std::string& name)
{
    return *patternModels_.at(name);
}

void ModelManager::createModels(std::map<std::string,AABB> spritesAABB)
{
    obstacleModels_["default"] = new ObstacleModel("obstacle", spritesAABB["obstacle"]);

    bulletModels_["default"] = new BulletModel("bullet", spritesAABB["bullet"], 3.0f);
    bulletModels_["enemy"] = new BulletModel("bullet_enemy", spritesAABB["bullet_enemy"], 3.0f);

    createPatterns();

    enemyModels_["default"] = new EnemyModel("enemy", spritesAABB["enemy"], getBulletModelByName("enemy"), getPatternModelByName("arcOfCircle"));
}

void ModelManager::createPatterns()
{
    // default pattern : 3 shoots
    std::vector<float> angles;
    angles.push_back(180.0f);
    angles.push_back(135.0f);
    angles.push_back(-135.0f);
    patternModels_["default"] = new PatternModel(5.0f, 0.5f, 240.0f, 4);
    patternModels_["default"]->init(angles, false);

    // circle pattern
    angles.clear();
    for (Uint32 i = 0; i < 18; i++)
    {
        angles.push_back(i * 20.0f);
    }
    patternModels_["circle"] = new PatternModel(5.0f, 0.5f, 240.0f, 5);
    patternModels_["circle"]->init(angles, false);

    // arc of circle pattern
    angles.clear();
    for (int i = -3; i <= 3; i++)
    {
        angles.push_back(i * 10.0f);
    }
    patternModels_["arcOfCircle"] = new PatternModel(5.0f, 0.5f, 240.0f, 5);
    patternModels_["arcOfCircle"]->init(angles, true);
}
