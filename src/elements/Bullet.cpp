#include "Bullet.h"
#include "ProgramConstants.h"
#include <iostream>

Bullet::Bullet(const AABB& aabb, const std::string& spriteName, float lifetime, Vector2f ori, float velocity) :
    Element(aabb, spriteName)
{
    // calculate frame number lifetime_ with second lifetime
    lifetime_ = int(lifetime*ProgramConstants::getInstance().getFps());

    // calculate dp_
    dp_ = ori * velocity/ProgramConstants::getInstance().getFps();

}

Bullet::Bullet(const BulletModel& model, Vector2f pos, Vector2f ori, float velocity) :
    Element(model, pos)
{
    // calculate frame number lifetime_ with second lifetime
    lifetime_ = int(model.lifetime_*ProgramConstants::getInstance().getFps());

    // calculate dp_
    dp_ = ori * velocity/ProgramConstants::getInstance().getFps();
}

Bullet::~Bullet()
{
    //dtor
}

void Bullet::move()
{
    aabb_.move(dp_);
    lifetime_--;
}

void Bullet::bounce(const Vector2f& normal, const Vector2f& tangent)
{
    Vector2f n = normal;
    n.normalize();

    Vector2f t = tangent;
    t.normalize();

    dp_ = t*dp_.dotProduct(t) + n*dp_.dotProduct(n)*-1.0f;
}

bool Bullet::lives()
{
    return lifetime_>0;
}
