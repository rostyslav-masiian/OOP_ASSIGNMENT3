#pragma once
#include "Vector2D.h"
#include "BoxCollider.h"

class Wall
{
protected: 
	float width;
	float height;
	int health = 50;
	Vector2D position;
public:
	Wall(int gridX, int gridY, float tileSize);
	void takeDamage(int amount);
	int getHealth() const;
	Vector2D getPosition() const;
	BoxCollider getCollider() const;
};

