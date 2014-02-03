#include "World.h"
#include <iostream>
#include <cmath>

World::World(float fps) :
    worldWidth_(600),
    worldHeight_(600),
    cameraWidth_(600),
    cameraHeight_(600),
    fps_(fps)
{

}

World::~World()
{
    delete collisionHandler_;
    // no need to delete Player because it is part of the elements_ vector
}

void World::setupLevel()
{
    camera_ = AABB(0,0,cameraWidth_,cameraHeight_);

    createObstacle(30, 30);
    createObstacle(100, 200);
    createObstacle(450, 300);

    spawnPlayer(300, 550);
}

void World::spawnPlayer(int x, int y)
{
    AABB playerAABB = spritesAABB_["player"];
    playerAABB.setPos(Vector2f(x,y));
    player_ = new Player(playerAABB, "player", 20.0f);
    elements_.push_back(player_);

    playerRelativeVelocity_ = player_->getMaxVelocity() / fps_;
}

void World::createObstacle(int x, int y)
{
    AABB aabb = spritesAABB_["obstacle"];
    aabb.setPos(Vector2f(x,y));
    elements_.push_back(new Obstacle(aabb, "obstacle"));
}

void World::update()
{
    // deal with events
    for (Uint32 i = 0; i < events_.size(); i++)
    {
        if (events_[i].id_ == events::MovePlayer)
        {
            player_->setSpeed(Vector2f(events_[i].x_,events_[i].y_)*playerRelativeVelocity_);
        }
    }
    clearEvents();

    // update positions
    for (Uint32 elementIndex = 0; elementIndex < elements_.size(); elementIndex++)
    {
        elements_[elementIndex]->move();
    }

    // set player speed to 0 (no inerty)
    // Todo : add an inerty for several frames/seconds
    player_->setSpeed(Vector2f());
}

void World::doCollisionCheck()
{

}

void World::addInputEvent(events::InputEvent event)
{
    events_.push_back(event);
}

void World::clearEvents()
{
    events_.clear();
}

void World::setSpritesAABB(const std::map<std::string,AABB>& spritesAABB)
{
    spritesAABB_ = spritesAABB;
}

const std::vector<Element*>& World::getElements()
{
    return elements_;
}

const int World::getCameraWidth()
{
    return cameraWidth_;
}

const int World::getCameraHeight()
{
    return cameraHeight_;
}
