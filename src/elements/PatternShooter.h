#ifndef PATTERNSHOOTER_H
#define PATTERNSHOOTER_H

#include "Bullet.h"
#include "time/Timer.h"
#include "models/BulletModel.h"
#include <vector>

class PatternShooter
{
    public:
        PatternShooter(const BulletModel& model, const float shootCadency, const float patternCadency, const float radius, const float velocity, const Uint32 shoots);
        virtual ~PatternShooter();

        void initCirclePattern();

        void computeTrajectories(Vector2f dir = Vector2f());
        /// shoot a salve of bullets
        std::vector<Bullet*>* shoot(Vector2f pos, Vector2f dir = Vector2f());
    protected:
    private:
        const float shootCadency_;      ///< frequency between 2 shoots in the pattern
        const float patternCadency_;    ///< frequency between 2 patterns
        const float radius_;
        const float bulletVelocity_;    ///< pixels per second
        const Uint32 patternShootNumber_;

        const BulletModel& bulletModel_;

        bool relativeAngles_;     ///< true : the pattern can be fired to a certain direction
        Uint32 currentShootNumber_;

        std::vector<float> angles_;
        std::vector<Trajectory*> trajectories_;

        Timer* bulletTimer_;
        Timer* patternTimer_;
};

#endif // PATTERNSHOOTER_H
