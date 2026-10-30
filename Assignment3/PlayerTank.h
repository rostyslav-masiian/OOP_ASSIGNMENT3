#pragma once
#include "Tank.h"
#include <SFML/Window/Keyboard.hpp>


class PlayerTank : public Tank
{
private:
	float angle = -1.5707963f;
	float turnSpeed = 2.0f;
public:
	PlayerTank(Vector2D startPos, float speed, int health = 1000);
	void handleInput();
	void move(float dt, const std::vector<Wall>& walls, const GameMap& gameMap) override;
	ProjectileOwner getProjectileOwner() const override;
};

