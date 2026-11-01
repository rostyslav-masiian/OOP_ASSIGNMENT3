#pragma once
#include "GameMap.h"
#include "Projectile.h"
#include "Tank.h"
#include "PlayerTank.h"
#include "BotTank.h"
#include "Wall.h"

#include <vector>
#include <memory>
#include "InputState.h"

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
	bool collidesWithOtherTank(const Tank& tank) const;
	bool isOutsideMap(const Projectile& p) const;
public:
	GameEngine(GameMap map, std::unique_ptr<PlayerTank> playerTank, std::vector< std::unique_ptr<BotTank>> bots, std::vector<Wall> walls);
	void update(float dt, const InputState& input);
	
	bool isGameOver() const;
	bool didPlayerWin() const;

	const GameMap& getMap() const { return gameMap; }
	const PlayerTank* getPlayer() const { return playerTank.get(); }
	const std::vector<std::unique_ptr<BotTank>>& getBots() const { return bots; }
	const std::vector<Projectile>& getProjectiles() const { return projectiles; }
	const std::vector<Wall>& getWalls() const { return walls; }

};

