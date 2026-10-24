#include "GameEngine.h"

GameEngine::GameEngine(GameMap map, std::unique_ptr<PlayerTank> playerTank, std::vector< std::unique_ptr<BotTank>> bots, std::vector<Wall> walls)
	: gameMap(std::move(map)), playerTank(std::move(playerTank)), bots(std::move(bots)), walls(std::move(walls)) {}

void GameEngine::removeDestroyed()
{
	std::erase_if(projectiles, [](const Projectile& p) {return !p.isAlive();});
	std::erase_if(walls, [](const Wall& w) {return w.isDestroyed(); });
	std::erase_if(bots, [](const BotTank& bt) {return !bt.isAlive(); });

}
void GameEngine::checkCollisions()
{
	for (auto& proj : projectiles)
	{
		for (auto& wall : walls)
		{
			if (!wall.isDestroyed() && proj.getCollider().intersectsWith(wall.getCollider()))
			{
				wall.takeDamage(proj.getDamage());
				proj.destroy();
				break;
			}
		}
		if (!proj.isAlive()) continue;

		if (playerTank && proj.getOwner() != playerTank.get())
		{
			if (playerTank->isAlive() && proj.getCollider().intersectsWith(playerTank->getCollider()))
			{
				playerTank->takeDamage(proj.getDamage());
				proj.destroy();
				break;
			}
		}

		for (auto& bot : bots)
		{
			if (bot && proj.getOwner() != bot.get())
			{
				if (bot->isAlive() && proj.getCollider().intersects(bot->getCollider()))
				{
					bot->takeDamage(proj.getDamage());
					proj.destroy();
					break;
				}
			}
		}
	}
}

void GameEngine::update(float dt)
{
	if (playerTank && playerTank->isAlive())
	{
		playerTank->handleInput();
		playerTank->updateCooldown(dt);
		playerTank->move(dt, walls, gameMap);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Space) && playerTank->canFire())
		{
			projectiles.push_back(playerTank->fire());
			playerTank->resetCooldown();
		}
	}
	for (auto& bot : bots)
	{
		if (bot && bot->isAlive() && playerTank)
		{
			bot->update(dt, *playerTank, walls, gameMap, projectiles);
		}
	}
	for (auto& proj : projectiles)
	{
		proj.move(dt);	
	}
	checkCollisions();
	removeDestroyed();
}


bool GameEngine::didPlayerWin()
{
	return bots.empty() && playerTank->isAlive();
}

bool GameEngine::isGameOver()
{
	
	return !playerTank || !playerTank->isAlive() || bots.empty();
}