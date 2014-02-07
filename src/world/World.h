#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <map>
#include <list>

#include "elements/Player.h"
#include "elements/Obstacle.h"
#include "events/InputEvent.h"
#include "AABB.h"
#include "CollisionHandler.h"

/// @file World.h

/// @class World
/// class managing the game world and its physics
class World
{
    public:
        World();
        virtual ~World();

        void setupLevel();

        void update();
        /// @return true if the player is dead
        bool doCollisionCheck();
        void doBulletCollisionCheck();
        void scroll();

        void spawnPlayer(int x, int y);
        void createObstacle(int x, int y);

        void createObstacleByModel(int x, int y, const std::string modelName = "default");

        void clearEvents();
        void clearElements();
        void addInputEvent(events::InputEvent event);

        void setSpritesAABB(const std::map<std::string,AABB>& spritesAABB);
        const Player* getPlayer();
        const std::vector<Element*>& getElements();
        const std::vector<const Element*>& getElementsToDraw();

    private:
        // constant data
        std::map<std::string,AABB> spritesAABB_;
        const int worldWidth_, worldHeight_;
        const float scrollingSpeed_;    // pixels per second

        float playerRelativeVelocity_;  // pixels per frame
        Vector2f cameraScrolling_;      // pixels per frame
        bool isScrolling_;

        // elements
        std::vector<Element*> elements_;
        std::list<Bullet*> playerBullets_;
        std::vector<const Element*> elementsToDraw_;
        Player* player_;

        // events
        std::vector<events::InputEvent> events_;

        // collisions
        CollisionHandler* collisionHandler_;

};

#endif // WORLD_H
