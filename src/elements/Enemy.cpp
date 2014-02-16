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

    animationTimer_ = new Timer(10.0f);
}

Enemy::Enemy(const EnemyModel& model, Vector2f pos) :
    Entity(model.aabb_, model.spriteName_, 0.0f)
{
    hp_ = 10;
    dp_ = Vector2f();

    aabb_.setPos(pos);

    animationTimer_ = new Timer(10.0f);

    initShooter(model.bulletModel_);
}

Enemy::~Enemy()
{
    delete animationTimer_;

    delete bulletShooter_;
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
    if (animationTimer_->stopped())
        animationTimer_->start();

    hp_--;
    if (hp_ == 0)
        return true;

    return false;
}

bool Enemy::invisible()
{
    if (!animationTimer_->hasTicked())
        return true;
    else
    {
        animationTimer_->reset();
        return false;
    }
}
