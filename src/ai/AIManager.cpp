#include "AIManager.h"
#include "elements/AIEnemy.h"

AIManager::AIManager()
{
    currentMaxId_ = 0;
}

AIManager::~AIManager()
{
    //dtor
}

AIEnemy* AIManager::getEnemyById(Uint32 id)
{
    return enemiesById_.at(id);
}

const ScriptedAI& AIManager::getAIById(Uint32 id) const
{
    return *AIs_.at(id);
}

void AIManager::createAI(AIEnemy* enemy)
{
    enemy->setAiId(currentMaxId_);
    AIs_[currentMaxId_] = new ScriptedAI(enemy->getAABB(), player_->getAABB(), false, KeyPositions, 400.0f, 200.0f);
    enemiesById_[currentMaxId_] = enemy;

    currentMaxId_++;
}

void AIManager::removeAI(Uint32 id)
{
    AIs_.erase(id);
    enemiesById_.erase(id);
}

void AIManager::update()
{
    events_.clear();

    for (std::map<Uint32,ScriptedAI*>::iterator it = AIs_.begin(); it != AIs_.end(); ++it)
    {
        ScriptedAI* ai = it->second;
        ai->update();

        for (Uint32 i = 0; i < ai->getCommands().size(); i++)
        {
            events_.push_back(AIEvent(it->first, ai->getCommands()[i]));
        }
    }
}

void AIManager::clear()
{
    events_.clear();
    AIs_.clear();
    enemiesById_.clear();

    currentMaxId_ = 0;
}

void AIManager::setPlayer(const Player* player)
{
    player_ = player;
}

const std::vector<AIEvent>& AIManager::getEvents() const
{
    return events_;
}

