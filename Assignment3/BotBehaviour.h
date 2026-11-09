#pragma once
#include <vector>
#include <memory>
#include <random>

#include "Wall.h"
#include "GameMap.h"

class BotTank;
class Tank;

class BotBehaviour
{
public:
	virtual void update(BotTank& bot, float dt, const std::vector<Wall>& walls, const GameMap& gameMap, const std::vector<const Tank*>& others) = 0;
	virtual ~BotBehaviour() = default; 
};

class PatrolBehaviour : public BotBehaviour
{
private:
	float patrolTime = 0.0f;
public:
	void update(BotTank& bot, float dt, const std::vector<Wall>& walls, const GameMap& gameMap, const std::vector<const Tank*>& others) override;
};

class ChaseBehaviour : public BotBehaviour
{
	void update(BotTank& bot, float dt, const std::vector<Wall>& walls, const GameMap& gameMap, const std::vector<const Tank*>& others) override;
};