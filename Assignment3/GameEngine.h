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
	void update();
	void handleFire(Tank& tank);
	bool isGameOver();
	bool didPlayerWin();
};

