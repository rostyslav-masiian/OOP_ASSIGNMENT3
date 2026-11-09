#pragma once
#include "Tank.h"


class PlayerTank : public Tank
{
private:
	float angle = -1.5707963f;
	float turnSpeed = 2.0f;
public:
	PlayerTank(Vector2D startPos, float speed, int health);
	
	void turnLeft(float dt);
	void turnRight(float dt);
	void moveForward(float dt, const std::vector<Wall>& walls, 
		const GameMap& gameMap, const std::vector<const Tank*>& others);


	
	void updateDirection();
	void update(float dt, const std::vector<Wall>& walls, const GameMap& gameMap, const std::vector<const Tank*>& others, std::vector<Projectile>& projectiles) override;
	ProjectileOwner getProjectileOwner() const override;
};

