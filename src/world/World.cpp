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

    createEnemyByModel(400, 800, true);
    createEnemyByModel(100, 800, true);
    createEnemyByModel(300, 40, true);
    createEnemyByModel(500, 200, true);
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

void World::createEnemyByModel(int x, int y, bool playerKnowledge, const std::string modelName /*= default*/)
{
    enemies_.push_back(new Enemy(ModelManager::getInstance().getEnemyModelByName(modelName), Vector2f(x,y)));
    if (playerKnowledge)
        enemies_.back()->setPlayer(player_);
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
                //bullet->initTrajectory();
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
    // enemies
    for (std::list<Enemy*>::iterator enemyIt = enemies_.begin(); enemyIt != enemies_.end(); ++enemyIt)
    {
        (*enemyIt)->move();
        Bullet* bullet = (*enemyIt)->shootToPlayer();
        if (bullet != NULL)
            {
                bullet->initTrajectory();
                enemyBullets_.push_back(bullet);
            }
    }
    // player bullets
    for (std::list<Bullet*>::iterator bulletIt = playerBullets_.begin(); bulletIt != playerBullets_.end(); ++bulletIt)
    {
        (*bulletIt)->move();
    }
    // enemy bullets
    for (std::list<Bullet*>::iterator bulletIt = enemyBullets_.begin(); bulletIt != enemyBullets_.end(); ++bulletIt)
    {
        (*bulletIt)->move();
    }

    player_->move();
}

bool World::doCollisionCheck()
{
    elementsToDraw_.clear();

    for (std::list<Enemy*>::iterator enemyIt = enemies_.begin(); enemyIt != enemies_.end(); ++enemyIt)
    {
        if (collisionHandler_->isInCamera((*enemyIt)->getAABB()) && !(*enemyIt)->invisible())
            elementsToDraw_.push_back(*enemyIt);
    }


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

    if (doEnemyBulletCollisionCheck())
    {
        std::cout << "DEAD" << std::endl;
        return true;
    }

    return false;
}

void World::doBulletCollisionCheck()
{
    for (std::list<Bullet*>::iterator bulletIt = playerBullets_.begin(); bulletIt != playerBullets_.end(); ++bulletIt)
    {
        Bullet* bullet = *bulletIt;
        const Circle* circle = dynamic_cast<const Circle*>(bullet->getCollisionModel());
        Uint32 bulletCollision = 0;

        bool bulletOnEnemy = false;
        // collision with enemy : destroy the bullet
        for (std::list<Enemy*>::iterator enemyIt = enemies_.begin(); enemyIt != enemies_.end(); ++enemyIt)
        {
            bulletOnEnemy = collisionHandler_->twoAABBCollisionCheck(bullet->getAABB(), (*enemyIt)->getAABB());
            if (bulletOnEnemy)
            {
                if ((*enemyIt)->injure())
                    enemies_.erase(enemyIt);
                break;
            }
        }

        if (bulletOnEnemy)
        {
            bulletIt = playerBullets_.erase(bulletIt);
            continue;
        }

        // collision with obstacle -> bounce
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

bool World::doEnemyBulletCollisionCheck()
{
   for (std::list<Bullet*>::iterator bulletIt = enemyBullets_.begin(); bulletIt != enemyBullets_.end(); ++bulletIt)
    {
        Bullet* bullet = *bulletIt;
        const Circle* circle = dynamic_cast<const Circle*>(bullet->getCollisionModel());
        Uint32 bulletCollision = 0;

        bool bulletOnPlayer = collisionHandler_->twoAABBCollisionCheck(player_->getAABB(), bullet->getAABB());
        if (bulletOnPlayer)
        {
            enemyBullets_.erase(bulletIt);
            return true;
        }

        // collision with obstacle -> bounce
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
            bulletIt = enemyBullets_.erase(bulletIt);
        }
        else
            if (collisionHandler_->isInCamera(bullet->getAABB()))
                elementsToDraw_.push_back(bullet);

        // segfault guard!
        if (enemyBullets_.empty())
                break;
    }

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
    enemies_.clear();
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
