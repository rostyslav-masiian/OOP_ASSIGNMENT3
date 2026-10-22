#pragma once
#include "Vector2D.h"

class Wall
{
protected: 
	int size;
	int health;
	Vector2D position;
public:
	void takeDamage(int amount);
	int getHealth() const;
	Vector2D getPosition() const;
};

