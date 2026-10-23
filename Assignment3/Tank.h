#pragma once
#include "Vector2D.h"
#include "Projectile.h"
#include "Wall.h"
#include "GameMap.h"

#include <memory>
#include "vector"

class Tank
{
protected:
	int size = 5;
	int health = 100;
	float speed = 10;
	Vector2D tankCenter;
	Vector2D direction = Vector2D(0, 0);

	float timeSinceLastShot = 0.0f;
	float timeCooldown = 0.5f;
public:
	
	int getSize() const;
	int getHealth() const;
	Vector2D getTankCenter() const;
	void takeDamage(int takenDamage);
	bool canFire();
	void updateCooldown(float dt);
	void resetCooldown();

	Projectile fire();
	virtual void move(float dt, const std::vector<Wall>& walls, const GameMap& gameMap) = 0;
	virtual ~Tank() = default;
};

