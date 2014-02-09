#include "Element.h"

Element::Element()
{
    //ctor
}

Element::Element(const AABB& aabb, const std::string &spriteName) :
    aabb_(aabb),
    spriteName_(spriteName),
    rotation_(0.0)
{
}

Element::Element(const ElementModel& model, Vector2f pos)
{
    aabb_ = model.aabb_;
    aabb_.setPos(pos);
    spriteName_ = model.spriteName_;
    rotation_ = 0.0;
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

const double Element::getRotation() const
{
    return rotation_;
}

void Element::setRotation(double rotation)
{
    rotation_ = rotation;
}

bool Element::isRotated() const
{
    return rotation_ != 0.0;
}
