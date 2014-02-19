#ifndef AIMANAGER_H
#define AIMANAGER_H

#include <map>
#include "AIEvent.h"
#include "ScriptedAI.h"

class AIEnemy;
class Player;

class AIManager
{
    public:
        AIManager();
        virtual ~AIManager();

        void setPlayer(const Player* player);

        void update();
        void createAI(AIEnemy* enemy);
        void removeAI(Uint32 id);
        void clear();

        AIEnemy* getEnemyById(Uint32 id);
        const ScriptedAI& getAIById(Uint32 id) const;
        const std::vector<AIEvent>& getEvents() const;
    protected:
    private:
        std::map<Uint32,ScriptedAI*> AIs_;
        std::map<Uint32, AIEnemy*> enemiesById_;
        std::vector<AIEvent> events_;

        Uint32 currentMaxId_;
        const Player* player_;
};

#endif // AIMANAGER_H
