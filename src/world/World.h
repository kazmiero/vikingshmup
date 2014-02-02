#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <map>
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
        World(float fps);
        virtual ~World();

        void setupLevel();

        void update();
        void doCollisionCheck();

        void spawnPlayer(int x, int y);
        void createObstacle(int x, int y);

        void clearEvents();
        void addInputEvent(events::InputEvent event);

        void setSpritesAABB(const std::map<std::string,AABB>& spritesAABB);
        const std::vector<Element*>& getElements();
        const int getCameraWidth();
        const int getCameraHeight();

    private:
        // constant data
        std::map<std::string,AABB> spritesAABB_;
        const int worldWidth_, worldHeight_;
        const int cameraWidth_, cameraHeight_;
        const float fps_;

        float playerRelativeVelocity_;
        AABB camera_;

        // elements
        std::vector<Element*> elements_;
        Player* player_;

        // events
        std::vector<events::InputEvent> events_;

        // collisions
        CollisionHandler* collisionHandler_;

};

#endif // WORLD_H
