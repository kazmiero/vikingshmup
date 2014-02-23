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

const AIModel& ModelManager::getAIModelByName(const std::string& name)
{
    return *aiModels_.at(name);
}

void ModelManager::createModels(std::map<std::string,AABB> spritesAABB)
{
    obstacleModels_["default"] = new ObstacleModel("obstacle", spritesAABB["obstacle"]);

    bulletModels_["default"] = new BulletModel("bullet", spritesAABB["bullet"], 3.0f);
    bulletModels_["enemy"] = new BulletModel("bullet_enemy", spritesAABB["bullet_enemy"], 3.0f);

    createPatterns();

    enemyModels_["default"] = new EnemyModel("enemy", spritesAABB["enemy"], 20.0f, getPatternModelByName("basic2"));
    enemyModels_["1"] = new EnemyModel("enemy", spritesAABB["enemy"], 20.0f, getPatternModelByName("basic1"));
    enemyModels_["2"] = new EnemyModel("enemy", spritesAABB["enemy"], 30.0f, getPatternModelByName("basic2"));
    enemyModels_["3"] = new EnemyModel("enemy", spritesAABB["enemy"], 30.0f, getPatternModelByName("circle"));
    enemyModels_["4"] = new EnemyModel("enemy", spritesAABB["enemy"], 30.0f, getPatternModelByName("arcOfCircle"));

    createAI();
}

void ModelManager::createPatterns()
{
    const BulletModel& bullet = getBulletModelByName("enemy");

    // default pattern : 3 shoots
    std::vector<float> angles;
    angles.push_back(180.0f);
    angles.push_back(135.0f);
    angles.push_back(-135.0f);
    patternModels_["default"] = new PatternModel(5.0f, 0.5f, 240.0f, 4, bullet);
    patternModels_["default"]->init(angles, false);

    // circle pattern
    angles.clear();
    for (Uint32 i = 0; i < 18; i++)
    {
        angles.push_back(i * 20.0f);
    }
    patternModels_["circle"] = new PatternModel(5.0f, 0.5f, 240.0f, 5, bullet);
    patternModels_["circle"]->init(angles, false);

    // arc of circle pattern
    angles.clear();
    for (int i = -3; i <= 3; i++)
    {
        angles.push_back(i * 10.0f);
    }
    patternModels_["arcOfCircle"] = new PatternModel(5.0f, 0.5f, 240.0f, 5, bullet);
    patternModels_["arcOfCircle"]->init(angles, true);

    angles.clear();
    angles.push_back(180.0f);
    patternModels_["basic1"] = new PatternModel(7.0f, 1.0f, 240.0f, 3, bullet);
    patternModels_["basic1"]->init(angles, false);

    angles.clear();
    angles.push_back(-10.0f);
    angles.push_back(10.0f);
    patternModels_["basic2"] = new PatternModel(7.0f, 1.0f, 240.0f, 1, bullet);
    patternModels_["basic2"]->init(angles, true);
}

void ModelManager::createAI()
{
    std::vector<Vector2f> points;
    points.push_back(Vector2f(0,400));
    aiModels_["1"] = new AIModel(false, Autofire, 500.0f, 0.0f);
    aiModels_["1"]->initPoints(points);

    points.clear();
    points.push_back(Vector2f(100,200));
    points.push_back(Vector2f(200,100));
    aiModels_["2"] = new AIModel(false, NearPlayer, 700.0f, 400.0f);
    aiModels_["2"]->initPoints(points);

    points.clear();
    points.push_back(Vector2f(-100,200));
    points.push_back(Vector2f(-200,100));
    aiModels_["2bis"] = new AIModel(false, NearPlayer, 700.0f, 400.0f);
    aiModels_["2bis"]->initPoints(points);

    points.clear();
    points.push_back(Vector2f(100, 0));
    points.push_back(Vector2f(50, 100));
    points.push_back(Vector2f(-50, -100));
    points.push_back(Vector2f(-100, 0));
    aiModels_["4"] = new AIModel(true, KeyPositions, 500.0f, 0.0f);
    aiModels_["4"]->initPoints(points);

    points.clear();
    points.push_back(Vector2f(-100, 0));
    points.push_back(Vector2f(-50, 100));
    points.push_back(Vector2f(50, -100));
    points.push_back(Vector2f(100, 0));
    aiModels_["4bis"] = new AIModel(true, KeyPositions, 500.0f, 0.0f);
    aiModels_["4bis"]->initPoints(points);
}
