#pragma once
#include "Tank.h"
#include "Projectile.h"
#include "Wall.h"
#include "GameMap.h"

#include <vector>
#include <cmath>
#include <algorithm>

class PlayerTank;
class Wall;
class GameMap;
class BotBehaviour;


class BotTank : public Tank
{
private:
	float patrolTimer = 0.0f;
	std::unique_ptr<BotBehaviour> botBehaviour;
	const Tank* target = nullptr;
	bool wantToFire = false;

public:
	BotTank(Vector2D startPos, float speed, int health);
	bool isSegmentIntersectingBox(const Vector2D& p1, const Vector2D& p2, const BoxCollider& box) const;
	bool hasLineOfSight(const Vector2D& botPos, const Vector2D& playerPos, const std::vector<Wall>& walls) const;
	ProjectileOwner getProjectileOwner() const override;

	void setTarget(const Tank* newTarget);
	bool canSeeTarget(const std::vector<Wall>& walls) const;
	Vector2D getTargetPosition() const;

	void requestFire();
	void update(float dt, const std::vector<Wall>& walls, const GameMap& gameMap, const std::vector<const Tank*>& others, std::vector<Projectile>& projectiles) override;
	void moveInCurrentDirection(float dt, const std::vector<Wall>& walls, const GameMap& gameMap, const std::vector<const Tank*>& others);
	
	void setBehaviour(std::unique_ptr<BotBehaviour> botBehaviour);
};
