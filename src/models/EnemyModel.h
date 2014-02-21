#ifndef ENEMYMODEL_H
#define ENEMYMODEL_H

#include "PatternModel.h"


class EnemyModel : public ElementModel
{
    public:
        EnemyModel(const std::string& spriteName, const AABB& aabb, const float maxVelocity, const PatternModel& patternModel);
        virtual ~EnemyModel();

        const float maxVelocity_;

        const PatternModel& patternModel_;

};

#endif // ENEMYMODEL_H
