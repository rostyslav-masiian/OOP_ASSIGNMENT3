#pragma once
#include "GameObject.h"

class Damageable : public GameObject
{
private:
	int health;
	int maxHealth;

public:
	explicit Damageable(int health) : health(health), maxHealth(health) {}

	void takeDamage(int amount) { health -= amount; }
	int getHealth() const { return health; }
	int getMaxHealth() const { return maxHealth; }

	bool isAlive() const override { return health > 0; }
};