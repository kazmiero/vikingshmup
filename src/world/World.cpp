#include "World.h"
#include <iostream>
#include <cmath>
#include "ProgramConstants.h"
#include "models/ModelManager.h"
#include "OBB.h"

World::World() :
    worldWidth_(600),
    worldHeight_(2400),
    scrollingSpeed_(20.0f),
    isScrolling_(true)
{
    cameraScrolling_ = Vector2f(0.0f,-scrollingSpeed_/ProgramConstants::getInstance().getFps());
    aiManager_ = new AIManager();
}

World::~World()
{
    delete aiManager_;
    delete collisionHandler_;
    // no need to delete player_ because it is part of the elements_ vector
}

void World::setupLevel()
{
    const float cameraHeight = ProgramConstants::getInstance().getCameraHeight();
    const float cameraWidth = ProgramConstants::getInstance().getCameraWidth();

    AABB::camera = AABB(0,worldHeight_-cameraHeight,cameraWidth,cameraHeight);
    collisionHandler_ = new CollisionHandler();

    spawnPlayer(300, 2350);
    aiManager_->setPlayer(player_);

    //createAIEnemyByModel(400, 700);
    createAIEnemyByModel(100, 1900, "1", "1");
    createAIEnemyByModel(300, 1900, "1", "1");
    createAIEnemyByModel(500, 1900, "1", "1");

    createAIEnemyByModel(-50, 1400, "2", "2");
    createAIEnemyByModel(-50, 1500, "2", "2");

    createAIEnemyByModel(650, 1400, "2", "2bis");
    createAIEnemyByModel(650, 1500, "2", "2bis");

    //createEnemyByModel(300, 40, true);
    //createEnemyByModel(500, 200, true);
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

void World::createAIEnemyByModel(int x, int y, const std::string modelName /*= "default"*/, const std::string aiModelName /*= "1"*/)
{
    enemies_.push_back(new AIEnemy(ModelManager::getInstance().getEnemyModelByName(modelName), Vector2f(x,y)));
    enemies_.back()->setPlayer(player_);
    aiManager_->createAI(dynamic_cast<AIEnemy*>(enemies_.back()), ModelManager::getInstance().getAIModelByName(aiModelName));
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

    // deal with ai
    aiManager_->update();
    for (Uint32 i = 0; i < aiManager_->getEvents().size(); i++)
    {
        AIEvent event = aiManager_->getEvents()[i];
        AIEnemy* enemy = aiManager_->getEnemyById(event.aiId_);

        if (event.command_ == Move)
        {
            const ScriptedAI& ai = aiManager_->getAIById(event.aiId_);
            enemy->initTrajectory(ai.getPoints(), ai.periodicTrajectory());
        }

        if (event.command_ == Shoot)
        {
            if (!enemy->isShooting() && collisionHandler_->isInCamera(enemy->getAABB()))
                enemy->setShooting(true);
        }
    }

    // update positions
    for (Uint32 elementIndex = 0; elementIndex < elements_.size(); elementIndex++)
    {
        elements_[elementIndex]->move();
    }
    // enemies
    for (std::list<Enemy*>::iterator enemyIt = enemies_.begin(); enemyIt != enemies_.end(); ++enemyIt)
    {
        Enemy* enemy = *enemyIt;
        enemy->move();

        if (!collisionHandler_->isInCamera(enemy->getAABB()))
            continue;

        if (enemy->patternShoot())
        {
            std::vector<Bullet*>* bullets = enemy->shootPattern();
            if (bullets != NULL)
            {
                enemyBullets_.insert(enemyBullets_.end(), bullets->begin(), bullets->end());
            }
        }
        else
        {
            Bullet* bullet = enemy->shoot();
            if (bullet != NULL)
                {
                    //bullet->initTrajectory();
                    enemyBullets_.push_back(bullet);
                }
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
                {
                    if ((*enemyIt)->hasAI())
                    {
                        AIEnemy* enemy = dynamic_cast<AIEnemy*>(*enemyIt);
                        aiManager_->removeAI(enemy->getAiId());
                    }
                    enemies_.erase(enemyIt);
                }
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
    aiManager_->clear();
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
