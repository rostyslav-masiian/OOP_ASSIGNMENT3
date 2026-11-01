#include "GameEngine.h"

GameEngine::GameEngine(GameMap map, std::unique_ptr<PlayerTank> playerTank, std::vector< std::unique_ptr<BotTank>> bots, std::vector<Wall> walls)
	: gameMap(std::move(map)), playerTank(std::move(playerTank)), bots(std::move(bots)), walls(std::move(walls)) {}

void GameEngine::removeDestroyed()
{
	std::erase_if(projectiles, [this](const Projectile& p) {return !p.isAlive() || isOutsideMap(p);});
	std::erase_if(walls, [](const Wall& w) {return w.isDestroyed(); });
	std::erase_if(bots, [](const std::unique_ptr<BotTank>& bot) {return !bot || !bot->isAlive(); });

}
void GameEngine::checkCollisions()
{
	for (Projectile& proj : projectiles)
	{
		for (Wall& wall : walls)
		{
			if (!wall.isDestroyed() && proj.getCollider().intersectsWith(wall.getCollider()))
			{
				wall.takeDamage(proj.getDamage());
				proj.destroy();
				break;
			}
		}
		if (!proj.isAlive()) continue;

		
		if (proj.getOwner() == ProjectileOwner::Bot)
		{
			if (playerTank && playerTank->isAlive() &&
				proj.getCollider().intersectsWith(playerTank->getCollider()))
			{
				playerTank->takeDamage(proj.getDamage());
				proj.destroy();
			}
			continue;
		}

		
		for (std::unique_ptr<BotTank>& bot : bots)
		{
			if (bot && bot->isAlive() &&
				proj.getCollider().intersects(bot->getCollider()))
			{
				bot->takeDamage(proj.getDamage());
				proj.destroy();
				break;
			}
		}
	}
}
bool GameEngine::isOutsideMap(const Projectile& p) const
{
	const float mapWidthPx = static_cast<float>(gameMap.getWidth()) * gameMap.getTileSize();
	const float mapHeightPx = static_cast<float>(gameMap.getHeight()) * gameMap.getTileSize();

	return p.getCenter().getX() <= 0 || p.getCenter().getY() <= 0 ||
		p.getCenter().getX() >= mapWidthPx || p.getCenter().getY() >= mapHeightPx;
}
bool GameEngine::collidesWithOtherTank(const Tank& tank) const
{
	BoxCollider box = tank.getCollider();

	if (playerTank && playerTank.get() != &tank && playerTank->isAlive() &&
		box.intersects(playerTank->getCollider()))
	{
		return true;
	}

	for (const std::unique_ptr<BotTank>& bot : bots)
	{
		if (bot && bot.get() != &tank && bot->isAlive() &&
			box.intersects(bot->getCollider()))
		{
			return true;
		}
	}
	return false;
}

void GameEngine::update(float dt, const InputState& input)
{
	for (auto& proj : projectiles)
	{
		proj.move(dt);
	}
	if (playerTank && playerTank->isAlive())
	{
		playerTank->setInput(input);
		playerTank->updateCooldown(dt);

		Vector2D previousPosition = playerTank->getCenter();
		playerTank->move(dt, walls, gameMap);
		if (collidesWithOtherTank(*playerTank))
		{
			playerTank->setTankCenter(previousPosition);
		}

		if (input.fire && playerTank->canFire())
		{
			projectiles.push_back(playerTank->fire());
		}
	}

	for (std::unique_ptr<BotTank>& bot : bots)
	{
		if (bot && bot->isAlive() && playerTank)
		{
			Vector2D previousPosition = bot->getCenter();
			bot->update(dt, *playerTank, walls, gameMap, projectiles);
			if (collidesWithOtherTank(*bot))
			{
				bot->setTankCenter(previousPosition);
			}
		}
	}

	checkCollisions();
	removeDestroyed();
}


bool GameEngine::didPlayerWin() const
{
	return bots.empty() && playerTank->isAlive();
}

bool GameEngine::isGameOver() const
{
	
	return !playerTank || !playerTank->isAlive() || bots.empty();
}