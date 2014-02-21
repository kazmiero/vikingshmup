#ifndef AIMODEL_H
#define AIMODEL_H

#include <vector>
#include "world/Vector2f.h"

typedef enum {Autofire, NearPlayer, KeyPositions} FireMode;

class AIModel
{
    public:
        AIModel(const bool periodicTrajectory, const FireMode firemode, const float moveTrigger, const float shootTrigger);
        virtual ~AIModel();

        void initPoints(const std::vector<Vector2f>& points);

        const bool periodicTrajectory_;
        const FireMode firemode_;
        const float distanceToPlayerMoveTrigger_;
        const float distanceToPlayerShootTrigger_;

        std::vector<Vector2f> points_;       ///< relative to the object starting position
};

#endif // AIMODEL_H
