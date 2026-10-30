#include "GameEngine.h"

GameEngine::GameEngine(GameMap map, std::unique_ptr<PlayerTank> playerTank, std::vector< std::unique_ptr<BotTank>> bots, std::vector<Wall> walls)
	: gameMap(std::move(map)), playerTank(std::move(playerTank)), bots(std::move(bots)), walls(std::move(walls)) {}

void GameEngine::removeDestroyed()
{
	std::erase_if(projectiles, [](const Projectile& p) {return !p.isAlive();});
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

void GameEngine::update(float dt)
{
	for (auto& proj : projectiles)
	{
		proj.move(dt);
	}
	std::erase_if(projectiles, [this](const Projectile& p) {
		return !p.isAlive() ||
			p.getCenter().getX() <= 0 ||
			p.getCenter().getY() <= 0 ||
			p.getCenter().getX() >= gameMap.getWidth() * gameMap.getTileSize() ||
			p.getCenter().getY() >= gameMap.getHeight() * gameMap.getTileSize();
		});
	if (playerTank && playerTank->isAlive())
	{
		playerTank->handleInput();

		playerTank->updateCooldown(dt);

		Vector2D previousPosition = playerTank->getTankCenter();
		playerTank->move(dt, walls, gameMap);

		for (const std::unique_ptr<BotTank>& bot : bots)
		{
			if (bot && bot->isAlive() &&
				playerTank->getCollider().intersects(bot->getCollider()))
			{
				playerTank->setTankCenter(previousPosition);
				break;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Space) && playerTank->canFire())
		{
			projectiles.push_back(playerTank->fire());
		}
	}

	for (std::unique_ptr<BotTank>& bot : bots)
	{
		if (bot && bot->isAlive() && playerTank)
		{
			Vector2D previousPosition = bot->getTankCenter();
			bot->update(dt, *playerTank, walls, gameMap, projectiles);
			for (const std::unique_ptr<BotTank>& other : bots)
			{
				if (other && other != bot && other->isAlive() &&
					bot->getCollider().intersects(other->getCollider()))
				{
					bot->setTankCenter(previousPosition);
					break;
				}
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