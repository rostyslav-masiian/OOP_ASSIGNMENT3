#include "BotBehaviour.h"
#include "BotTank.h"


Vector2D getRandomDirection()
{
	static const std::vector<Vector2D> directions = {
		Vector2D(0.0f, -1.0f),
		Vector2D(0.0f, 1.0f),
		Vector2D(-1.0f, 0.0f),
		Vector2D(1.0f, 0.0f)
	};


	std::random_device rd;
	static std::mt19937 rng{ rd() };

	std::uniform_int_distribution<size_t> dist(0, directions.size() - 1);

	return directions[dist(rng)].normalized();
}

void PatrolBehaviour::update(BotTank& bot, float dt, const std::vector<Wall>& walls, const GameMap& gameMap, const std::vector<const Tank*>& others)
{
	if (bot.canSeeTarget(walls))
	{
		bot.setBehaviour(std::make_unique<ChaseBehaviour>());
		return;
	}
	patrolTime -= dt;

	if (patrolTime <= 0.0f)
	{
		patrolTime = 2.0f + (rand() % 20) / 10.0f;
		bot.setDirection(getRandomDirection());
	}
	bot.moveInCurrentDirection(dt, walls, gameMap, others);
}

void ChaseBehaviour::update(BotTank& bot, float dt, const std::vector<Wall>& walls, const GameMap& gameMap, const std::vector<const Tank*>& others)
{
	if (!bot.canSeeTarget(walls))
	{
		bot.setBehaviour(std::make_unique<PatrolBehaviour>());
		return;
	}
	Vector2D toTarget = bot.getTargetPosition() - bot.getCenter();
	if (toTarget.length() > 0.001f)
	{
		bot.setDirection(toTarget.normalized());
	}
	bot.moveInCurrentDirection(dt, walls, gameMap, others);

	bot.requestFire();
}