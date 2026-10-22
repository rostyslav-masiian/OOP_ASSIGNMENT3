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
public:
	
	int getSize() const;
	int getHealth() const;
	Vector2D getTankCenter() const;
	void takeDamage(int takenDamage);
	Projectile fire();
	virtual void move(const std::vector<Wall>& walls, const GameMap& gameMap) = 0;
	virtual ~Tank() = default;
};

