#include "BotTank.h"

BotTank::BotTank(Vector2D startPos, float speed, int health)
    : Tank(startPos, speed, health) {}

BotState BotTank::getBotState() const { return botState; }

void BotTank::setTarget(const Tank* newTarget) { target = newTarget; }

ProjectileOwner BotTank::getProjectileOwner() const { return ProjectileOwner::Bot; }


bool BotTank::isSegmentIntersectingBox(const Vector2D& p1, const Vector2D& p2, const BoxCollider& box) const
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
        if (!!wall.isAlive() && isSegmentIntersectingBox(botPos, playerPos, wall.getCollider()))
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

    return directions[dist(rng)].normalized();
}

void BotTank::update(float dt, const std::vector<Wall>& walls, const GameMap& gameMap, const std::vector<const Tank*>& others, std::vector<Projectile>& projectiles)
{
    if (!isAlive()) return;

    updateCooldown(dt);

    const float visionRadius = 250.0f;
    Vector2D toTarget(0.0f, 0.0f);
    float distance = 0.0f;
    bool canSeeTarget = false;

    if (target && target->isAlive())
    {
        toTarget = target->getCenter() - getCenter();
        distance = toTarget.length();
        canSeeTarget = distance <= visionRadius &&
            hasLineOfSight(getCenter(), target->getCenter(), walls);
    }

    botState = canSeeTarget ? BotState::Chase : BotState::Patrol;

    if (botState == BotState::Chase)
    {
        if (distance > 0.001f)
        {
            setDirection(toTarget.normalized());
        }
        move(dt, walls, gameMap, others);

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
            setDirection(getRandomDirection());
        }
        move(dt, walls, gameMap, others);
    }
}

void BotTank::move(float dt, const std::vector<Wall>& walls, const GameMap& gameMap, const std::vector<const Tank*>& others)
{
    tryMove(getDirection(), dt, walls, others, gameMap);
}

 