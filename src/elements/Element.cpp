#include "Element.h"

Element::Element()
{
    //ctor
}

Element::Element(const AABB& aabb, const std::string &spriteName) :
    aabb_(aabb),
    spriteName_(spriteName)
{
}

Element::~Element()
{
    //dtor
}

const AABB& Element::getAABB() const
{
    return aabb_;
}

const std::string& Element::getSpriteName() const
{
    return spriteName_;
}
