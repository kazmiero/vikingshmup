#ifndef OBSTACLEMODEL_H
#define OBSTACLEMODEL_H

#include "ElementModel.h"


class ObstacleModel : public ElementModel
{
    public:
        ObstacleModel(const std::string& spriteName, const AABB& aabb);
        virtual ~ObstacleModel();
    protected:
    private:
};

#endif // OBSTACLEMODEL_H
