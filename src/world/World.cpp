#include "World.h"
#include <iostream>
#include <cmath>

World::World(float fps) :
    worldWidth_(600),
    worldHeight_(1200),
    cameraWidth_(600),
    cameraHeight_(600),
    fps_(fps),
    scrollingSpeed_(20.0f),
    isScrolling_(true)
{
    cameraScrolling_ = Vector2f(0.0f,-scrollingSpeed_/fps_);
}

World::~World()
{
    delete collisionHandler_;
    // no need to delete player_ because it is part of the elements_ vector
}

void World::setupLevel()
{
    AABB::camera = AABB(0,worldHeight_-cameraHeight_,cameraWidth_,cameraHeight_);
    collisionHandler_ = new CollisionHandler();

    createObstacle(30, 30);
    createObstacle(100, 200);
    createObstacle(450, 300);

    createObstacle(20, 480);
    createObstacle(150, 600);
    createObstacle(400, 750);

    createObstacle(200, 880);
    createObstacle(10, 950);
    createObstacle(500, 1000);

    spawnPlayer(300, 1150);
}

void World::spawnPlayer(int x, int y)
{
    AABB playerAABB = spritesAABB_["player"];
    AABB cannonAABB = spritesAABB_["cannon"];
    playerAABB.setPos(Vector2f(x,y));
    cannonAABB.setPos(Vector2f(x,y));
    player_ = new Player(playerAABB, "player", 20.0f, cannonAABB, "cannon");

    playerRelativeVelocity_ = player_->getMaxVelocity() / fps_;
}

void World::createObstacle(int x, int y)
{
    AABB aabb = spritesAABB_["obstacle"];
    aabb.setPos(Vector2f(x,y));
    elements_.push_back(new Obstacle(aabb, "obstacle"));
}

void World::scroll()
{
    isScrolling_ = AABB::camera.getPos().y_ > 0;

    if (isScrolling_)
        AABB::camera.move(cameraScrolling_);
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
        else if (events_[i].id_ == events::OrientCannon)
        {
            player_->changeOrientation(events_[i].x_ < 0);
        }
    }
    clearEvents();

    // update positions
    for (Uint32 elementIndex = 0; elementIndex < elements_.size(); elementIndex++)
    {
        elements_[elementIndex]->move();
    }
    player_->move();
}

bool World::doCollisionCheck()
{
    elementsToDraw_.clear();

    bool playerCollision = false;
    bool playerCollisionWithObstacle = false;
    for (Uint32 elementIndex = 0; elementIndex < elements_.size(); elementIndex++)
    {
        playerCollisionWithObstacle = playerCollisionWithObstacle
                || collisionHandler_->twoAABBCollisionCheck(player_->getAABB(), elements_[elementIndex]->getAABB());

        if(collisionHandler_->isInCamera(elements_[elementIndex]->getAABB()))
            elementsToDraw_.push_back(elements_[elementIndex]);
    }

    playerCollision = playerCollisionWithObstacle
        || collisionHandler_->cameraCollisionCheck(player_->getAABB());

    if (playerCollision)
    {
        player_->back();
        bool scrollingCollision = collisionHandler_->scrollingCollisionCheck(player_->getAABB());
        if (isScrolling_ && scrollingCollision)
            player_->scroll(cameraScrolling_);
        if (isScrolling_ && scrollingCollision && playerCollisionWithObstacle)
        {
            std::cout << "DEAD" << std::endl;
            return true;
        }
    }
    else if (isScrolling_)
        player_->scroll(cameraScrolling_);
    // set player speed to 0 (no inerty)
    // Todo : add an inerty for several frames/seconds
    player_->setSpeed(Vector2f());

    //elementsToDraw_.push_back(player_);

    return false;
}

void World::addInputEvent(events::InputEvent event)
{
    events_.push_back(event);
}

void World::clearEvents()
{
    events_.clear();
}

void World::clearElements()
{
    elements_.clear();
}

void World::setSpritesAABB(const std::map<std::string,AABB>& spritesAABB)
{
    spritesAABB_ = spritesAABB;
}

const Player* World::getPlayer()
{
    return player_;
}

const std::vector<Element*>& World::getElements()
{
    return elements_;
}

const std::vector<const Element*>& World::getElementsToDraw()
{
    return elementsToDraw_;
}

const int World::getCameraWidth()
{
    return cameraWidth_;
}

const int World::getCameraHeight()
{
    return cameraHeight_;
}
