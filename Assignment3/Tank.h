#pragma once
#include "Vector2D.h"
#include "Projectile.h"
#include "Wall.h"
#include "GameMap.h"
#include "BoxCollider.h"
#include <algorithm>
#include <memory>
#include "vector"
#include "Damageable.h"
class Tank : public Damageable
{
private:
	int size = 32;
	Vector2D tankCenter;
	float speed = 10;
	Vector2D direction = Vector2D(0, 0);

	float timeSinceLastShot = 0.0f;
	float timeCooldown = 0.5f;

	bool collidesAt(const Vector2D& center, const std::vector<Wall>& walls, const std::vector<const Tank*>& others) const;

protected:
	void setDirection(const Vector2D& newDirection);
	void tryMove(const Vector2D& dir, float dt, const std::vector<Wall>& walls,	const std::vector<const Tank*>& others,	const GameMap& gameMap);
	
public:
	Tank(Vector2D startPos, float speed, int health);
	
	int getSize() const;
	Vector2D getCenter() const override;
	Vector2D getDirection() const;
	bool canFire();
	void setTankCenter(const Vector2D& newCenter);
	void updateCooldown(float dt);
	void resetCooldown();
	BoxCollider getCollider() const;
	Projectile fire();
	virtual void update(float dt, const std::vector<Wall>& walls, const GameMap& gameMap, const std::vector<const Tank*>& others, std::vector<Projectile>& projectiles) = 0;
	virtual void move(float dt, const std::vector<Wall>& walls, const GameMap& gameMap, const std::vector<const Tank*>& others) = 0;
	virtual ProjectileOwner getProjectileOwner() const = 0;
	virtual ~Tank() = default;
};

