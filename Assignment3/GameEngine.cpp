#include "GameEngine.h"

GameEngine::GameEngine(GameMap map, std::unique_ptr<PlayerTank> playerTank, std::vector< std::unique_ptr<BotTank>> bots, std::vector<Wall> walls)
	: gameMap(std::move(map)), playerTank(std::move(playerTank)), bots(std::move(bots)), walls(std::move(walls)) {}

void GameEngine::removeDestroyed()
{

}
void GameEngine::checkCollisions()
{

}
void GameEngine::handleFire(Tank& tank)
{

}

bool GameEngine::didPlayerWin()
{
	return 0;
}

bool GameEngine::isGameOver()
{
	return 0;
}