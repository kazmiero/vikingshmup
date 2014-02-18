#include "PatternShooter.h"
#include "ProgramConstants.h"

PatternShooter::PatternShooter(const BulletModel& model, const float shootCadency, const float patternCadency, const float radius, const float velocity, const Uint32 shoots) :
    shootCadency_(shootCadency),
    patternCadency_(patternCadency),
    radius_(radius),
    bulletVelocity_(velocity/ProgramConstants::getInstance().getFps()),
    patternShootNumber_(shoots),
    bulletModel_(model)
{
    bulletTimer_ = new Timer(shootCadency_);
    patternTimer_ = new Timer(patternCadency_);
    //patternTimer_->start();
    //bulletTimer_->start();

    currentShootNumber_ = 0;
}

PatternShooter::~PatternShooter()
{
    delete bulletTimer_;
    delete patternTimer_;
}

void PatternShooter::initCirclePattern()
{
    for (Uint32 i = 0; i < 18; i++)
    {
        angles_.push_back(i * 20.0f);
    }
    relativeAngles_ = false;

    trajectories_.resize(angles_.size());
    computeTrajectories();
}

void PatternShooter::computeTrajectories(Vector2f dir /* = Vector2f*/)
{
    for (Uint32 i = 0; i < angles_.size(); i++)
    {
        Vector2f initialSpeed = Vector2f::getOrientationByAngle(angles_[i]);
        if (relativeAngles_)
        {
            initialSpeed += dir;
            initialSpeed.normalize();
        }
        initialSpeed *= bulletVelocity_;

        trajectories_[i] = new Trajectory(initialSpeed);
    }
}

std::vector<Bullet*>* PatternShooter::shoot(Vector2f pos, Vector2f dir /* = Vector2f()*/)
{
    if (patternTimer_->hasTicked() && currentShootNumber_ < patternShootNumber_)
    {
        if (bulletTimer_->hasTicked())
        {
            bulletTimer_->reset();
            bulletTimer_->start();
            currentShootNumber_++;

            std::vector<Bullet*>* bullets = new std::vector<Bullet*>();

            for (Uint32 i = 0; i < trajectories_.size(); i++)
            {
                Vector2f bulletPos = pos + Vector2f::getOrientationByAngle(angles_[i])*radius_;
                bullets->push_back(new Bullet(bulletModel_, bulletPos, *trajectories_[i]));
            }

            return bullets;
        }
    }
    else if (patternTimer_->hasTicked() && currentShootNumber_ >= patternShootNumber_)
    {
        patternTimer_->reset();
        patternTimer_->start();
        currentShootNumber_ = 0;
    }

    return NULL;
}
