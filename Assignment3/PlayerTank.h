#pragma once
#include "Tank.h"
#include <SFML/Window/Keyboard.hpp>


class PlayerTank : public Tank
{
public:
	PlayerTank(Vector2D startPos, float speed, int health);
	void handleInput();
	void move(float dt, const std::vector<Wall>& walls, const GameMap& gameMap) override;
	bool isAlive() const;
};

