#pragma once
#include "Tank.h"
#include <SFML/Window/Keyboard.hpp>


class PlayerTank : public Tank
{
public:
	using Tank::Tank;
	void handleInput();
	void move(float dt, const std::vector<Wall>& walls, const GameMap& gameMap) override;
	bool isAlive() const;
};

