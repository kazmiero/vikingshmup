#ifndef ELEMENT_H
#define ELEMENT_H

#include <string>
#include "world/AABB.h"

/// @file Element.h

/// @class Element
/// An element of the world. It has an AABB representing its position and collision properties, and a sprite name for rendering purpose
class Element
{
    public:
        Element();
        Element(const AABB& aabb, const std::string &spriteName);
        virtual ~Element();

        const AABB& getAABB() const;
        const std::string& getSpriteName() const;

        /// move if it is possible, else do nothing
        virtual void move() = 0;

    protected:
        AABB aabb_;
        std::string spriteName_;
};

#endif // ELEMENT_H
