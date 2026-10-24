#pragma once
#include "Tank.h"
#include <vector>

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

public:
	using Tank::Tank;
	BotState getBotState() const;
	bool isSegmentIntersectingBox(const Vector2D& p1, const Vector2D& p2, const BoxCollider& box);
	bool hasLineOfSight(const Vector2D& botPos, const Vector2D& playerPos, const std::vector<Wall>& walls);
	bool isAlive() const;

	void update(float dt, const PlayerTank& player, const std::vector<Wall>& walls, const GameMap& gameMap, std::vector<Projectile>& projectiles);
	void move(float dt, const std::vector<Wall>& walls, const GameMap& gameMap) override;

};
