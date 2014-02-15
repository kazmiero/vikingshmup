#include "Enemy.h"

Enemy::Enemy() : Entity()
{
    //ctor
}

Enemy::Enemy(const AABB& aabb, const std::string& spriteName, float maxVelocity) :
    Entity(aabb, spriteName, maxVelocity)
{
    hp_ = 10;
    dp_ = Vector2f();
}

Enemy::Enemy(const EnemyModel& model, Vector2f pos) :
    Entity(model.aabb_, model.spriteName_, 0.0f)
{
    hp_ = 10;
    dp_ = Vector2f();

    aabb_.setPos(pos);

    initShooter(model.bulletModel_);
}

Enemy::~Enemy()
{
    //dtor
}

void Enemy::initShooter(const BulletModel& model)
{
    bulletShooter_ = new BulletShooter(model, 5.0f, 240.0f);
}

Bullet* Enemy::shoot()
{
    Vector2f pos = aabb_.getPos() + Vector2f(0.0f, aabb_.getH());
    Vector2f ori = Vector2f(0,1);

    return bulletShooter_->shoot(pos, ori);
}

Bullet* Enemy::shootToPlayer()
{
    Vector2f ori = player_->getAABB().getPos() - aabb_.getPos();
    ori.normalize();
    Vector2f pos = aabb_.getPos() + Vector2f(0.0f, aabb_.getH());

    return bulletShooter_->shoot(pos, ori);
}

void Enemy::setPlayer(const Player* player)
{
    player_ = player;
}

bool Enemy::injure()
{
    hp_--;
    if (hp_ == 0)
        return true;

    return false;
}
