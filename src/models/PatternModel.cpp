#include "PatternModel.h"

PatternModel::PatternModel(const float shootCadency, const float patternCadency, const float velocity, const Uint32 shoots, const BulletModel& bulletModel) :
    shootCadency_(shootCadency),
    patternCadency_(patternCadency),
    velocity_(velocity),
    shoots_(shoots),
    bulletModel_(bulletModel)
{
    //ctor
}

PatternModel::~PatternModel()
{
    //dtor
}

void PatternModel::init(const std::vector<float>& angles, bool relativeAngles)
{
    angles_ = angles;
    relativeAngles_ = relativeAngles;
}
