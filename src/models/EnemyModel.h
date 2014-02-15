#ifndef ENEMYMODEL_H
#define ENEMYMODEL_H

#include "BulletModel.h"


class EnemyModel : public ElementModel
{
    public:
        EnemyModel(const std::string& spriteName, const AABB& aabb, const BulletModel& bulletModel);
        virtual ~EnemyModel();

        const BulletModel& bulletModel_;

};

#endif // ENEMYMODEL_H
