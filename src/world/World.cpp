#include "World.h"
#include <iostream>
#include <cmath>
#include "ProgramConstants.h"
#include "models/ModelManager.h"
#include "OBB.h"

World::World() :
    worldWidth_(600),
    worldHeight_(1200),
    scrollingSpeed_(20.0f),
    isScrolling_(true)
{
    cameraScrolling_ = Vector2f(0.0f,-scrollingSpeed_/ProgramConstants::getInstance().getFps());
}

World::~World()
{
    delete collisionHandler_;
    // no need to delete player_ because it is part of the elements_ vector
}

void World::setupLevel()
{
    const float cameraHeight = ProgramConstants::getInstance().getCameraHeight();
    const float cameraWidth = ProgramConstants::getInstance().getCameraWidth();

    AABB::camera = AABB(0,worldHeight_-cameraHeight,cameraWidth,cameraHeight);
    collisionHandler_ = new CollisionHandler();

    createObstacleByModel(70, 30);
    createObstacleByModel(130, 200, 30.0);
    createObstacleByModel(450, 300);

    createObstacleByModel(60, 480);
    createObstacleByModel(150, 600);
    createObstacleByModel(400, 750);

    createObstacleByModel(200, 880, 45.0);
    createObstacleByModel(50, 950);
    createObstacleByModel(500, 1000, 45.0);

    spawnPlayer(300, 1150);
}

void World::spawnPlayer(int x, int y)
{
    AABB playerAABB = spritesAABB_["player"];
    AABB cannonAABB = spritesAABB_["cannon"];
    playerAABB.setPos(Vector2f(x,y));
    cannonAABB.setPos(Vector2f(x,y));
    player_ = new Player(playerAABB, "player", 20.0f, cannonAABB, "cannon");
    player_->initShooter(ModelManager::getInstance().getBulletModelByName("default"));

    playerRelativeVelocity_ = player_->getMaxVelocity() / ProgramConstants::getInstance().getFps();
}

void World::createObstacle(int x, int y)
{
    AABB aabb = spritesAABB_["obstacle"];
    aabb.setPos(Vector2f(x,y));
    elements_.push_back(new Obstacle(aabb, "obstacle"));
}

void World::createObstacleByModel(int x, int y, double rotation /*= 0.0*/, const std::string modelName /*= default*/)
{
    elements_.push_back(new Obstacle(ModelManager::getInstance().getObstacleModelByName(modelName), Vector2f(x,y), rotation));
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
        else if (events_[i].id_ == events::Shoot)
        {
            Bullet* bullet = player_->shoot();
            if (bullet != NULL)
            {
                bullet->initTrajectory();
                playerBullets_.push_back(bullet);
            }
        }
    }
    clearEvents();

    // update positions
    for (Uint32 elementIndex = 0; elementIndex < elements_.size(); elementIndex++)
    {
        elements_[elementIndex]->move();
    }
    // bullets
    for (std::list<Bullet*>::iterator bulletIt = playerBullets_.begin(); bulletIt != playerBullets_.end(); ++bulletIt)
    {
        (*bulletIt)->move();
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
        const OBB* obb = dynamic_cast<const OBB*>(elements_[elementIndex]->getCollisionModel());

        playerCollisionWithObstacle = playerCollisionWithObstacle
                //|| collisionHandler_->twoAABBCollisionCheck(player_->getAABB(), elements_[elementIndex]->getAABB());
                || collisionHandler_->twoPolygonsCollisionCheck(OBB(player_->getAABB()), *obb);

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

    doBulletCollisionCheck();

    return false;
}

void World::doBulletCollisionCheck()
{
    for (std::list<Bullet*>::iterator bulletIt = playerBullets_.begin(); bulletIt != playerBullets_.end(); ++bulletIt)
    {
        Bullet* bullet = *bulletIt;
        const Circle* circle = dynamic_cast<const Circle*>(bullet->getCollisionModel());
        Uint32 bulletCollision = 0;

        for (Uint32 elementIndex = 0; elementIndex < elements_.size(); elementIndex++)
        {
            const OBB* obb = dynamic_cast<const OBB*>(elements_[elementIndex]->getCollisionModel());
            Vector2f normal, tangent;

            bulletCollision = collisionHandler_->circlePolygonCollisionCheck(*circle, *obb, normal, tangent);
            // does it optimize ?
            if (bulletCollision)
            {
                if (bulletCollision == 1)
                    bullet->bounce(normal, tangent);

                break;
            }
        }

        if (bulletCollision == 2 ||!bullet->lives())
        {
            bulletIt = playerBullets_.erase(bulletIt);
        }
        else
            if (collisionHandler_->isInCamera(bullet->getAABB()))
                elementsToDraw_.push_back(bullet);

        // segfault guard!
        if (playerBullets_.empty())
                break;
    }
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
    playerBullets_.clear();
    enemyBullets_.clear();
}

void World::setSpritesAABB(const std::map<std::string,AABB>& spritesAABB)
{
    spritesAABB_ = spritesAABB;
    ModelManager::getInstance().createModels(spritesAABB_);
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
