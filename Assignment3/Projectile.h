#pragma once
#include "Vector2D.h"
#include "CircleCollider.h"
#include "GameObject.h"
enum class ProjectileOwner
{
	Player,
	Bot
};

class Projectile : public GameObject
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
	Vector2D getCenter() const override;
	bool isAlive() const override;
	Vector2D getDirection() const;
	float getRadius() const;
	int getDamage() const;
	float getSpeed() const;
	CircleCollider getCollider() const;
	void destroy();
	ProjectileOwner getOwner() const;


};