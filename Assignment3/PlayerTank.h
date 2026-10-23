#pragma once
#include "Tank.h"
class PlayerTank : public Tank
{
public:
	using Tank::Tank;
	void move(float dt, const std::vector<Wall>& walls, const GameMap& gameMap) override;
};

