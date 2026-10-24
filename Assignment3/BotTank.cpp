#include "BotTank.h"
#include "Wall.h"
#include "PlayerTank.h"
#include "GameMap.h"

#include <cmath>
#include <algorithm>
#include <random>

BotState BotTank::getBotState() const { return botState; }
bool BotTank::isAlive() const { return health > 0; }

bool BotTank::isSegmentIntersectingBox(const Vector2D& p1, const Vector2D& p2, const BoxCollider& box)
{
    float minX = box.getPosition().getX();
    float maxX = minX + box.getWidth();
    float minY = box.getPosition().getY();
    float maxY = minY + box.getHeight();

    
    float tMin = 0.0f;
    float tMax = 1.0f;

    float dx = p2.getX() - p1.getX();
    float dy = p2.getY() - p1.getY();

    
    if (std::abs(dx) < 0.0001f)
    {
        if (p1.getX() < minX || p1.getX() > maxX) return false;
    }
    else
    {
        float t1 = (minX - p1.getX()) / dx;
        float t2 = (maxX - p1.getX()) / dx;
        tMin = std::max(tMin, std::min(t1, t2));
        tMax = std::min(tMax, std::max(t1, t2));
    }

    
    if (std::abs(dy) < 0.0001f)
    {
        if (p1.getY() < minY || p1.getY() > maxY) return false;
    }
    else
    {
        float t1 = (minY - p1.getY()) / dy;
        float t2 = (maxY - p1.getY()) / dy;
        tMin = std::max(tMin, std::min(t1, t2));
        tMax = std::min(tMax, std::max(t1, t2));
    }

    return tMin <= tMax;
}


bool BotTank::hasLineOfSight(const Vector2D& botPos, const Vector2D& playerPos, const std::vector<Wall>& walls)
{
    for (const auto& wall : walls)
    {
        if (!wall.isDestroyed() && isSegmentIntersectingBox(botPos, playerPos, wall.getCollider()))
        {
            return false; 
        }
    }
    return true;
}


static Vector2D getRandomDirection()
{
    static const std::vector<Vector2D> directions = {
        Vector2D(0.0f, -1.0f), 
        Vector2D(0.0f, 1.0f), 
        Vector2D(-1.0f, 0.0f), 
        Vector2D(1.0f, 0.0f)   
    };

    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<size_t> dist(0, directions.size() - 1);

    return directions[dist(rng)];
}

void BotTank::update(float dt, const PlayerTank& player, const std::vector<Wall>& walls, const GameMap& gameMap, std::vector<Projectile>& projectiles)
{
    
    updateCooldown(dt);

    
    float dx = player.getTankCenter().getX() - tankCenter.getX();
    float dy = player.getTankCenter().getY() - tankCenter.getY();
    float distance = std::sqrt(dx * dx + dy * dy);

    float agroRadius = 300.0f;

    
    bool canSeePlayer = (distance <= agroRadius && distance > 0.0001f) &&
        hasLineOfSight(tankCenter, player.getTankCenter(), walls);

    if (canSeePlayer)
    {
        
        botState = BotState::Chase;
        direction = Vector2D(dx / distance, dy / distance);

        if (canFire())
        {
            projectiles.push_back(fire());
            resetCooldown();
        }

        
        patrolTimer = 0.0f;
    }
    else
    {
        
        botState = BotState::Patrol;

        
        patrolTimer += dt;

        
        if ((direction.getX() == 0.0f && direction.getY() == 0.0f) || patrolTimer >= 2.5f)
        {
            direction = getRandomDirection();
            patrolTimer = 0.0f;
        }
    }

    
    move(dt, walls, gameMap);
}

void BotTank::move(float dt, const std::vector<Wall>& walls, const GameMap& gameMap)
{
	if (direction.getX() == 0.0f && direction.getY() == 0.0f)
	{
		return;
	}

	float speedModifier = gameMap.getSpeedModifier(tankCenter);
	float moveDistance = speed * speedModifier * dt;
	float halfSize = size / 2.0f;


	float mapSizeX = static_cast<float>(gameMap.getWidth() * gameMap.getTileSize());
	float mapSizeY = static_cast<float>(gameMap.getHeight() * gameMap.getTileSize());


	float nextX = tankCenter.getX() + direction.getX() * moveDistance;
	std::clamp(nextX, halfSize, mapSizeX - halfSize);

    Vector2D potentialTopLeftX(nextX - halfSize, tankCenter.getY() - halfSize);
    BoxCollider colX(potentialTopLeftX, static_cast<float>(size), static_cast<float>(size));

    bool collideX = false;
    for (const auto& wall : walls)
    {
        if (colX.intersects(wall.getCollider()))
        {
            collideX = true;
            break;
        }
    }

    if (!collideX)
    {
        tankCenter.setX(nextX);
    }


    float nextY = tankCenter.getY() + direction.getY() * moveDistance;
    std::clamp(nextY, halfSize, mapSizeY - halfSize);

    Vector2D potentialTopLeftY(tankCenter.getX() - halfSize, nextY - halfSize);
    BoxCollider colY(potentialTopLeftY, static_cast<float>(size), static_cast<float>(size));

    bool collideY = false;
    for (const auto& wall : walls)
    {
        if (colY.intersects(wall.getCollider()))
        {
            collideX = true;
            break;
        }
    }

    if (!collideY)
    {
        tankCenter.setY(nextY);
    }
    if (collideX && collideY)
    {
        if (rand() % 2 == 0)
        {
            direction = Vector2D(-direction.getY(), direction.getX());
        }
        else
        {
            direction = Vector2D(direction.getY(), -direction.getX());
        }

    }
}