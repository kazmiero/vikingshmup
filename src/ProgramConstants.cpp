#include "ProgramConstants.h"

ProgramConstants* ProgramConstants::instance_ = NULL;

ProgramConstants& ProgramConstants::getInstance()
{
    if (instance_ == NULL)
        instance_ = new ProgramConstants();

    return *instance_;
}

ProgramConstants::ProgramConstants() :
    fps_(60.0f),
    cameraWidth_(600),
    cameraHeight_(600),
    spritesDir_("../ressource/sprite"),
    menusDir_("../ressource/menus")
{
}

ProgramConstants::~ProgramConstants()
{
    //dtor
}

const float ProgramConstants::getFps() const
{
    return fps_;
}

const int ProgramConstants::getCameraWidth() const
{
    return cameraWidth_;
}

const int ProgramConstants::getCameraHeight() const
{
    return cameraHeight_;
}

const std::string& ProgramConstants::getSpritesDir() const
{
    return spritesDir_;
}

const std::string& ProgramConstants::getMenusDir() const
{
    return menusDir_;
}


