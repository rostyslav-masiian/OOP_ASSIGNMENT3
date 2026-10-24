#pragma once
#include "Vector2D.h"
#include "Projectile.h"
#include "Wall.h"
#include "GameMap.h"
#include "BoxCollider.h"
#include <algorithm>
#include <memory>
#include "vector"

class Tank
{
protected:
	int size = 32;
	int health = 100;
	float speed = 10;
	Vector2D tankCenter;
	Vector2D direction = Vector2D(0, 0);

	float timeSinceLastShot = 0.0f;
	float timeCooldown = 0.5f;
public:
	Tank(Vector2D startPos, float speed, int health);
	
	int getSize() const;
	int getHealth() const;
	Vector2D getTankCenter() const;
	Vector2D getDirection() const;
	void takeDamage(int takenDamage);
	bool canFire();
	void updateCooldown(float dt);
	void resetCooldown();
	BoxCollider getCollider() const;
	Projectile fire();
	virtual void move(float dt, const std::vector<Wall>& walls, const GameMap& gameMap) = 0;
	virtual ~Tank() = default;
};

