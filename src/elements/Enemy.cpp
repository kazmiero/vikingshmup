#include "Enemy.h"

Enemy::Enemy(const AABB& aabb, const std::string& spriteName, float maxVelocity) :
    Entity(aabb, spriteName, maxVelocity)
{
    hp_ = 10;
    dp_ = Vector2f();

    animationTimer_ = new Timer(10.0f);
}

Enemy::Enemy(const EnemyModel& model, Vector2f pos) :
    Entity(model.aabb_, model.spriteName_, model.maxVelocity_)
{
    hp_ = 10;
    dp_ = Vector2f();

    aabb_.setPos(pos);

    animationTimer_ = new Timer(10.0f);

    patternShoot_ = true;
    aimAtPlayer_ = true;

    initShooter(model.patternModel_);
}

Enemy::~Enemy()
{
    delete animationTimer_;

    if (bulletShooter_ != NULL)
        delete bulletShooter_;

    if (patternShooter_ != NULL)
        delete patternShooter_;
}

void Enemy::initShooter(const BulletModel& model)
{
    if (!patternShoot_)
        bulletShooter_ = new BulletShooter(model, 5.0f, 240.0f);
    else
    {
        patternShooter_ = new PatternShooter(model, 5.0f, 0.5f, 240.0f, 5);
        patternShooter_->setRadius(0.7f*aabb_.getH());
        patternShooter_->initArcOfCirclePattern();
    }
}

void Enemy::initShooter(const PatternModel& patternModel)
{
    patternShoot_ = true;
    patternShooter_ = new PatternShooter(patternModel);

    patternShooter_->setRadius(0.7f*aabb_.getH());
}

Bullet* Enemy::shoot()
{
    Vector2f pos = aabb_.getPos() + Vector2f(0.0f, aabb_.getH());
    Vector2f ori = Vector2f(0,1);

    if (aimAtPlayer_)
    {
        ori = player_->getAABB().getPos() - aabb_.getPos();
        ori.normalize();
    }

    return bulletShooter_->shoot(pos, ori);
}

std::vector<Bullet*>* Enemy::shootPattern()
{
    Vector2f ori = Vector2f();

    if (aimAtPlayer_)
    {
        ori = player_->getAABB().getPos() - aabb_.getPos();
        ori.normalize();
    }

    return patternShooter_->shoot(aabb_.getPos(), ori);
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

bool Enemy::patternShoot() const
{
    return patternShoot_;
}

bool Enemy::hasAI() const
{
    return false;
}
