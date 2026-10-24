#include "BotTank.h"
#include "Wall.h"
#include "PlayerTank.h"
#include "GameMap.h"

#include <cmath>
#include <algorithm>
#include <random>


BotTank::BotTank(Vector2D startPos, float speed, int health)
    : Tank(startPos, speed, health) {}

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

    
    std::random_device rd;
    static std::mt19937 rng{ rd() };

    std::uniform_int_distribution<size_t> dist(0, directions.size() - 1);

    return directions[dist(rng)];
}

void BotTank::update(float dt, const PlayerTank& player, const std::vector<Wall>& walls, const GameMap& gameMap, std::vector<Projectile>& projectiles)
{
    if (!isAlive()) return;

    updateCooldown(dt);

    Vector2D botPos = getTankCenter();
    Vector2D playerPos = player.getTankCenter();

    float dx = playerPos.getX() - botPos.getX();
    float dy = playerPos.getY() - botPos.getY();
    float distance = std::sqrt(dx * dx + dy * dy);

    float visionRadius = 250.0f; 

    
    bool canSeePlayer = (distance <= visionRadius) && hasLineOfSight(botPos, playerPos, walls);

    if (canSeePlayer)
    {
        botState = BotState::Chase;
    }
    else
    {
        botState = BotState::Patrol;
    }

    if (botState == BotState::Chase)
    {
        
        if (distance > 0.001f)
        {
            direction = Vector2D(dx / distance, dy / distance);
        }
        move(dt, walls, gameMap);

        if (canFire())
        {
            projectiles.push_back(fire());
        }
    }
    else 
    {
        
        patrolTimer -= dt;
        if (patrolTimer <= 0.0f)
        {
            patrolTimer = 2.0f + (rand() % 20) / 10.0f;
            int dirIndex = rand() % 4;
            if (dirIndex == 0) direction = Vector2D(0.0f, -1.0f);
            else if (dirIndex == 1) direction = Vector2D(0.0f, 1.0f);
            else if (dirIndex == 2) direction = Vector2D(-1.0f, 0.0f);
            else direction = Vector2D(1.0f, 0.0f);
        }
        move(dt, walls, gameMap);
    }
}

void BotTank::move(float dt, const std::vector<Wall>& walls, const GameMap& gameMap)
{
    float modifier = gameMap.getSpeedModifier(tankCenter);
    float moveDistance = speed * modifier * dt;

    float halfSize = static_cast<float>(size) / 2.0f;
    float mapSizeX = gameMap.getWidth() * gameMap.getTileSize();
    float mapSizeY = gameMap.getHeight() * gameMap.getTileSize();

    
    float nextX = tankCenter.getX() + direction.getX() * moveDistance;
    nextX = std::clamp(nextX, halfSize, mapSizeX - halfSize);

    Vector2D testPosPosX(nextX, tankCenter.getY());
    Vector2D topLeftX(testPosPosX.getX() - halfSize, testPosPosX.getY() - halfSize);
    BoxCollider testBoxX(topLeftX, static_cast<float>(size), static_cast<float>(size));

    bool collideX = false;
    for (const auto& wall : walls)
    {
        if (!wall.isDestroyed() && testBoxX.intersects(wall.getCollider()))
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
    nextY = std::clamp(nextY, halfSize, mapSizeY - halfSize);

    Vector2D testPosPosY(tankCenter.getX(), nextY);
    Vector2D topLeftY(testPosPosY.getX() - halfSize, testPosPosY.getY() - halfSize);
    BoxCollider testBoxY(topLeftY, static_cast<float>(size), static_cast<float>(size));

    bool collideY = false;
    for (const auto& wall : walls)
    {
        if (!wall.isDestroyed() && testBoxY.intersects(wall.getCollider()))
        {
            collideY = true;
            break;
        }
    }
    if (!collideY)
    {
        tankCenter.setY(nextY);
    }
}