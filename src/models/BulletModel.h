#ifndef BULLETMODEL_H
#define BULLETMODEL_H

#include "ElementModel.h"


class BulletModel : public ElementModel
{
    public:
        BulletModel(const std::string& spriteName, const AABB& aabb, const float lifetime);
        virtual ~BulletModel();

        const float lifetime_; ///< seconds
};

#endif // BULLETMODEL_H
