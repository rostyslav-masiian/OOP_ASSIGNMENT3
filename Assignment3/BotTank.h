#pragma once
#include "Tank.h"
#include "Projectile.h"
#include "Wall.h"
#include "GameMap.h"

#include <vector>
#include <cmath>
#include <algorithm>
#include <random>
class PlayerTank;
class Wall;
class GameMap;

enum BotState
{
	Patrol,
	Chase
};

class BotTank : public Tank
{
private:
	float patrolTimer = 0.0f; 
	BotState botState = BotState::Patrol;
	const Tank* target = nullptr;

public:
	BotTank(Vector2D startPos, float speed, int health);
	BotState getBotState() const;
	bool isSegmentIntersectingBox(const Vector2D& p1, const Vector2D& p2, const BoxCollider& box) const;
	bool hasLineOfSight(const Vector2D& botPos, const Vector2D& playerPos, const std::vector<Wall>& walls);
	ProjectileOwner getProjectileOwner() const override;
	void setTarget(const Tank* newTarget);

	void update(float dt, const std::vector<Wall>& walls, const GameMap& gameMap, const std::vector<const Tank*>& others, std::vector<Projectile>& projectiles) override;
	void move(float dt, const std::vector<Wall>& walls, const GameMap& gameMap, const std::vector<const Tank*>& others) override;
};
