#ifndef ELEMENTMODEL_H
#define ELEMENTMODEL_H

#include "world/AABB.h"
#include <string>

class ElementModel
{
    public:
        ElementModel(const std::string& spriteName, const AABB& aabb);
        virtual ~ElementModel();

        const std::string spriteName_;
        const AABB aabb_;
};

#endif // ELEMENTMODEL_H
