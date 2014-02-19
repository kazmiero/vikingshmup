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
        void initTrajectory(const std::vector<Vector2f>& points);

        const Uint32 getAiId() const;

        virtual bool hasAI() const;
        virtual void move();
    protected:
    private:
        Uint32 aiId_;
        Trajectory* trajectory_;
};

#endif // AIENEMY_H
