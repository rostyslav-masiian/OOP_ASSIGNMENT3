#include "GameEngine.h"
#include "Command.h"

GameEngine::GameEngine(GameMap map, std::unique_ptr<PlayerTank> playerTank, std::vector<std::unique_ptr<BotTank>> bots, std::vector<Wall> walls)
	: gameMap(std::move(map)), playerTank(std::move(playerTank)), bots(std::move(bots)), walls(std::move(walls))

{
	for (std::unique_ptr<BotTank>& bot : this->bots)
	{
		if (bot) bot->setTarget(this->playerTank.get());
	}
}

void GameEngine::removeDestroyed()
{
	std::erase_if(projectiles, [this](const Projectile& p) {return !p.isAlive() || isOutsideMap(p);});
	std::erase_if(walls, [](const Wall& w) {return !w.isAlive(); });
	std::erase_if(bots, [](const std::unique_ptr<BotTank>& bot) {return !bot || !bot->isAlive(); });

}

void GameEngine::turnPlayerLeft(float dt)
{
	if (getState() != GameState::Running) return;
	if (playerTank && playerTank->isAlive()) playerTank->turnLeft(dt);
}
void GameEngine::turnPlayerRight(float dt)
{
	if (getState() != GameState::Running) return;
	if (playerTank && playerTank->isAlive()) playerTank->turnRight(dt);

}
void GameEngine::movePlayerForward(float dt)
{
	if (getState() != GameState::Running) return;
	if (!playerTank || !playerTank->isAlive()) return;
	std::vector<Tank*> tanks = allTanks();
	std::vector<const Tank*> obstacles(tanks.begin(), tanks.end());
	playerTank->moveForward(dt, walls, gameMap, obstacles);

}

void GameEngine::playerFire()
{
	if (playerTank->canFire())
	{
		projectiles.push_back(playerTank->fire());
	}
}

bool GameEngine::isOutsideMap(const Projectile& p) const
{
	const float mapWidthPx = static_cast<float>(gameMap.getWidth()) * gameMap.getTileSize();
	const float mapHeightPx = static_cast<float>(gameMap.getHeight()) * gameMap.getTileSize();

	return p.getCenter().getX() <= 0 || p.getCenter().getY() <= 0 ||
		p.getCenter().getX() >= mapWidthPx || p.getCenter().getY() >= mapHeightPx;
}

static void applyHit(Damageable& target, Projectile& proj)
{
	target.takeDamage(proj.getDamage());
	proj.destroy();
}

void GameEngine::checkCollisions(const std::vector<Tank*>& tanks)
{
	for (Projectile& proj : projectiles)
	{
		for (Wall& wall : walls)
		{
			if (wall.isAlive() && proj.getCollider().intersectsWith(wall.getCollider()))
			{
				applyHit(wall, proj);
				break;
			}
		}
		if (!proj.isAlive()) continue;

		for (Tank* tank : tanks)
		{
			if (tank->getProjectileOwner() == proj.getOwner()) continue;

			if (tank->isAlive() && proj.getCollider().intersects(tank->getCollider()))
			{
				applyHit(*tank, proj);
				break;
			}
		}
	}
}

std::vector<Tank*> GameEngine::allTanks() const
{
	std::vector<Tank*> tanks;
	if (playerTank) tanks.push_back(playerTank.get());
	for (const std::unique_ptr<BotTank>& bot : bots)
	{
		if (bot) tanks.push_back(bot.get());
	}
	return tanks;
}

void GameEngine::update(float dt, std::vector<std::unique_ptr<Command>>& commands)
{
	for (const auto& cmd : commands)
	{
		cmd->execute(*this, dt);
	}
	
	if (getState() != GameState::Running) return;

	for (Projectile& proj : projectiles)
	{
		proj.move(dt);
	}


	std::vector<Tank*> tanks = allTanks();
	std::vector<const Tank*> obstacles(tanks.begin(), tanks.end());

	for (Tank* tank : tanks)
	{
		if (tank->isAlive())
		{
			tank->update(dt, walls, gameMap, obstacles, projectiles);
		}
	}

	checkCollisions(tanks);
	removeDestroyed();
}

GameState GameEngine::getState() const
{
	if (!playerTank || !playerTank->isAlive()) return GameState::PlayerLost;
	if (bots.empty()) return GameState::PlayerWon;
	if (paused) return GameState::Paused;
	return GameState::Running;
}

void GameEngine::togglePause()
{
	GameState state = getState();
	if (state == GameState::Running || state == GameState::Paused)
	{
		paused = !paused;
	}
}