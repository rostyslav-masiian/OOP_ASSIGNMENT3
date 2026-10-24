#pragma once
#include "GameMap.h"
#include "Projectile.h"
#include "Tank.h"
#include "PlayerTank.h"
#include "BotTank.h"
#include "Wall.h"

#include <vector>
#include <memory>

class GameEngine
{
private:
	

	GameMap gameMap;
	std::unique_ptr<PlayerTank> playerTank;
	std::vector< std::unique_ptr<BotTank>> bots;
	std::vector<Projectile> projectiles;
	std::vector<Wall> walls;

	void removeDestroyed();
	void checkCollisions();
public:
	GameEngine(GameMap map, std::unique_ptr<PlayerTank> playerTank, std::vector< std::unique_ptr<BotTank>> bots, std::vector<Wall> walls);
	void update(float dt);
	bool isGameOver() const;
	bool didPlayerWin() const;

	const GameMap& getMap() const { return gameMap; }
	const PlayerTank* getPlayer() const { return playerTank.get(); }
	const std::vector<std::unique_ptr<BotTank>>& getBots() const { return bots; }
	const std::vector<Projectile>& getProjectiles() const { return projectiles; }
	const std::vector<Wall>& getWalls() const { return walls; }

};

