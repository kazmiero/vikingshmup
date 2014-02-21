#ifndef MODELMANAGER_H
#define MODELMANAGER_H

#include "PatternModel.h"
#include "ObstacleModel.h"
#include "EnemyModel.h"
#include "AIModel.h"
#include <map>

class ModelManager
{
    public:
        static ModelManager& getInstance();

        const ObstacleModel& getObstacleModelByName(const std::string& name);
        const BulletModel& getBulletModelByName(const std::string& name);
        const EnemyModel& getEnemyModelByName(const std::string& name);
        const PatternModel& getPatternModelByName(const std::string& name);
        const AIModel& getAIModelByName(const std::string& name);

        void createModels(std::map<std::string,AABB> spritesAABB);
        void createPatterns();
        void createAI();

    private:
        ModelManager();
        static ModelManager* instance_;
        virtual ~ModelManager();

        std::map<std::string, ObstacleModel*> obstacleModels_;
        std::map<std::string, BulletModel*> bulletModels_;
        std::map<std::string, EnemyModel*> enemyModels_;
        std::map<std::string, PatternModel*> patternModels_;
        std::map<std::string, AIModel*> aiModels_;
};

#endif // MODELMANAGER_H
