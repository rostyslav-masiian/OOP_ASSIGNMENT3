#pragma once
#include "Tank.h"
#include <vector>

class PlayerTank;
class Wall;
class GameMap;

enum BotState
{
	Patrolling,
	Attacking
};

class BotTank : public Tank
{
private:
	BotState state;

public:
	BotState getBotState() const;
	void update(const PlayerTank& player, const std::vector<Wall>& walls);
	using Tank::Tank;
	void move(float dt, const std::vector<Wall>& walls, const GameMap& gameMap) override;

};
