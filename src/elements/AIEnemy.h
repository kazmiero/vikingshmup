#ifndef AIENEMY_H
#define AIENEMY_H

#include "Enemy.h"
#include "ai/ScriptedAI.h"
#include "Trajectory.h"


class AIEnemy : public Enemy
{
    public:
        AIEnemy(const EnemyModel& model, Vector2f pos);
        virtual ~AIEnemy();

        void setAiId(Uint32 aiId);
        void initTrajectory(const std::vector<Vector2f>& points, bool periodicTrajectory);

        const Uint32 getAiId() const;

        virtual std::vector<Bullet*>* shootPattern();
        bool isShooting() const;
        void setShooting(bool shooting);
        bool autofire() const;
        void setAutofire(bool autofire);

        virtual bool hasAI() const;
        virtual void move();
    protected:
    private:
        bool autofire_;

        Uint32 aiId_;
        Trajectory* trajectory_;
        bool shootingOnePattern_;
};

#endif // AIENEMY_H
