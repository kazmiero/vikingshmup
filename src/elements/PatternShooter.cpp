#include "PatternShooter.h"
#include "ProgramConstants.h"

PatternShooter::PatternShooter(const BulletModel& model, const float shootCadency, const float patternCadency, const float velocity, const Uint32 shoots) :
    shootCadency_(shootCadency),
    patternCadency_(patternCadency),
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

PatternShooter::PatternShooter(const PatternModel& patternModel) :
    shootCadency_(patternModel.shootCadency_),
    patternCadency_(patternModel.patternCadency_),
    bulletVelocity_(patternModel.velocity_/ProgramConstants::getInstance().getFps()),
    patternShootNumber_(patternModel.shoots_),
    bulletModel_(patternModel.bulletModel_)
{
    bulletTimer_ = new Timer(shootCadency_);
    patternTimer_ = new Timer(patternCadency_);
    //patternTimer_->start();
    //bulletTimer_->start();

    currentShootNumber_ = 0;

    angles_ = patternModel.angles_;
    relativeAngles_ = patternModel.relativeAngles_;
    trajectories_.resize(angles_.size());
    computeTrajectories();
}

PatternShooter::~PatternShooter()
{
    delete bulletTimer_;
    delete patternTimer_;
}

void PatternShooter::setRadius(float radius)
{
    radius_ = radius;
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

void PatternShooter::initArcOfCirclePattern()
{
    for (int i = -3; i <= 3; i++)
    {
        angles_.push_back(i * 10.0f);
    }
    relativeAngles_ = true;

    trajectories_.resize(angles_.size());
    computeTrajectories();
}

void PatternShooter::computeTrajectories(Vector2f dir /* = Vector2f*/)
{
    float dirAngle = Vector2f::getAngleByOrientation(dir);

    for (Uint32 i = 0; i < angles_.size(); i++)
    {
        Vector2f initialSpeed = Vector2f::getOrientationByAngle(angles_[i]);
        if (relativeAngles_)
        {
            float angle = angles_[i] + dirAngle;
            initialSpeed = Vector2f::getOrientationByAngle(angle);
        }
        initialSpeed *= bulletVelocity_;

        trajectories_[i] = new Trajectory(initialSpeed);
    }
}

std::vector<Bullet*>* PatternShooter::shoot(Vector2f pos, Vector2f dir /* = Vector2f()*/)
{

    if (currentShootNumber_ == 0 && relativeAngles_)
        computeTrajectories(dir);

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
                Vector2f dir = trajectories_[i]->getCurrentSpeed();
                dir.normalize();
                Vector2f bulletPos = pos + dir*radius_;
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

std::vector<Bullet*>* PatternShooter::shootOnePattern(Vector2f pos, bool& stillShooting, Vector2f dir /*= Vector2f*/)
{
    if (!patternTimer_->hasTicked())
        return NULL;

    if (currentShootNumber_ == 0 && relativeAngles_)
        computeTrajectories(dir);

    if (currentShootNumber_ < patternShootNumber_)
    {
        if (bulletTimer_->hasTicked())
        {
            bulletTimer_->reset();
            bulletTimer_->start();
            currentShootNumber_++;

            std::vector<Bullet*>* bullets = new std::vector<Bullet*>();

            for (Uint32 i = 0; i < trajectories_.size(); i++)
            {
                Vector2f dir = trajectories_[i]->getCurrentSpeed();
                dir.normalize();
                Vector2f bulletPos = pos + dir*radius_;
                bullets->push_back(new Bullet(bulletModel_, bulletPos, *trajectories_[i]));
            }

            return bullets;
        }
    }
    else
    {
        currentShootNumber_ = 0;
        stillShooting = false;
        patternTimer_->reset();
        patternTimer_->start();
    }

    return NULL;
}
