#pragma once
#include "Vector2D.h"
#include "CircleCollider.h"

enum class ProjectileOwner
{
	Player,
	Bot
};

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
	ProjectileOwner ownerType;

public:
	Projectile(Vector2D projCenter, Vector2D direction, ProjectileOwner ownerType);
	void move(float dt);
	Vector2D getCenter() const;
	Vector2D getDirection() const;
	float getRadius() const;
	int getDamage() const;
	float getSpeed() const;
	CircleCollider getCollider() const;

	void destroy();
	bool isAlive() const;
	ProjectileOwner getOwner() const;


};