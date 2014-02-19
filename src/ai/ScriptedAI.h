#ifndef SCRIPTEDAI_H
#define SCRIPTEDAI_H

#include <vector>
#include "world/AABB.h"
#include "AIEvent.h"

typedef enum {Autofire, NearPlayer, KeyPositions} FireMode;

class ScriptedAI
{
    public:
        ScriptedAI(const AABB& myAABB, const AABB& playerAABB, bool periodicTrajectory, FireMode firemode, float moveTrigger, float shootTrigger);
        virtual ~ScriptedAI();

        void initTrajectoryPoints();

        void update();
        const std::vector<AICommand>& getCommands() const;
        const std::vector<Vector2f>& getPoints() const;
    protected:
    private:
        // data
        const AABB& myAABB_;
        const AABB& playerAABB_;
        std::vector<Vector2f> trajectoryPoints_;
        std::vector<AICommand> commands_;

        bool hasMoved_;

        // parameters
        const bool periodicTrajectory_;
        const FireMode firemode_;     ///< if there is an autofire, no shoot event
        const float distanceToPlayerMoveTrigger_;
        const float distanceToPlayerShootTrigger_;
};

#endif // SCRIPTEDAI_H
