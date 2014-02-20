#ifndef ENEMYMODEL_H
#define ENEMYMODEL_H

#include "BulletModel.h"
#include "PatternModel.h"


class EnemyModel : public ElementModel
{
    public:
        EnemyModel(const std::string& spriteName, const AABB& aabb, const BulletModel& bulletModel, const PatternModel& patternModel);
        virtual ~EnemyModel();

        const BulletModel& bulletModel_;
        const PatternModel& patternModel_;

};

#endif // ENEMYMODEL_H
