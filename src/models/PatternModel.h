#ifndef PATTERNMODEL_H
#define PATTERNMODEL_H

#include <SDL2/SDL.h>
#include <vector>
#include "BulletModel.h"

class PatternModel
{
    public:
        PatternModel(const float shootCadency, const float patternCadency, const float velocity, const Uint32 shoots, const BulletModel& bulletModel);
        virtual ~PatternModel();

        void init(const std::vector<float>& angles, bool relativeAngles);

        const float shootCadency_;
        const float patternCadency_;
        const float velocity_;
        const Uint32 shoots_;

        const BulletModel& bulletModel_;

        bool relativeAngles_;
        std::vector<float> angles_;
};

#endif // PATTERNMODEL_H
