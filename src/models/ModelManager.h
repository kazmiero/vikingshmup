#ifndef MODELMANAGER_H
#define MODELMANAGER_H

#include "ObstacleModel.h"
#include "BulletModel.h"
#include <map>

class ModelManager
{
    public:
        static ModelManager& getInstance();

        const ObstacleModel& getObstacleModelByName(const std::string& name);
        const BulletModel& getBulletModelByName(const std::string& name);

        void createModels(std::map<std::string,AABB> spritesAABB);

    private:
        ModelManager();
        static ModelManager* instance_;
        virtual ~ModelManager();

        std::map<std::string, ObstacleModel*> obstacleModels_;
        std::map<std::string, BulletModel*> bulletModels_;
};

#endif // MODELMANAGER_H