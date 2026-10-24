#pragma once
#include "Vector2D.h"
#include "CircleCollider.h"

class Tank;

class Projectile
{
protected:
	int damage = 34;
	float speed = 200;
	float radius = 8;
	float lifespan = 10;
	bool destroyed = false;

	Vector2D projCenter;
	Vector2D direction;
	Tank* owner = nullptr;
	

public:
	Projectile(Vector2D projCenter, Vector2D direction, Tank* owner);
	void move(float dt);
	Vector2D getCenter() const;
	float getRadius() const;
	int getDamage() const;
	float getSpeed() const;
	CircleCollider getCollider() const;

	void destroy();
	bool isAlive() const;
	Tank* getOwner() const;

};

