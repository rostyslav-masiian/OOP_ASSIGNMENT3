#pragma once
#include "Tank.h"
#include "InputState.h"


class PlayerTank : public Tank
{
private:
	float angle = -1.5707963f;
	float turnSpeed = 2.0f;
	InputState input;
public:
	PlayerTank(Vector2D startPos, float speed, int health = 1000);
	void handleInput();
	void update(float dt, const std::vector<Wall>& walls, const GameMap& gameMap, const std::vector<const Tank*>& others, std::vector<Projectile>& projectiles) override;
	void move(float dt, const std::vector<Wall>& walls, const GameMap& gameMap, const std::vector<const Tank*>& others) override;
	ProjectileOwner getProjectileOwner() const override;
	void setInput(const InputState& newInput) { input = newInput; }
};

