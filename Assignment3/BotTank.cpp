#include "BotTank.h"
#include "BotBehaviour.h"


BotTank::BotTank(Vector2D startPos, float speed, int health)
    : Tank(startPos, speed, health) {}

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


bool BotTank::hasLineOfSight(const Vector2D& botPos, const Vector2D& playerPos, const std::vector<Wall>& walls) const
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

void BotTank::setBehaviour(std::unique_ptr<BotBehaviour> newBotBehaviour) { botBehaviour = std::move(newBotBehaviour);  }

void BotTank::moveInCurrentDirection(float dt, const std::vector<Wall>& walls, const GameMap& gameMap, const std::vector<const Tank*>& others)
{
    tryMove(getDirection(), dt, walls, others, gameMap);
}

Vector2D BotTank::getTargetPosition() const 
{ 
    if (!target)
    {
        return Vector2D(0, 0);
    }
    return target->getCenter();
}

void BotTank::requestFire() { wantToFire = true; }

void BotTank::update(float dt, const std::vector<Wall>& walls, const GameMap& gameMap, const std::vector<const Tank*>& others, std::vector<Projectile>& projectiles)
{
    if (!isAlive()) return;

    updateCooldown(dt);
    wantToFire = false;

    if (botBehaviour)
    {
        botBehaviour->update(*this, dt, walls, gameMap, others);
    }
    else
    {
        botBehaviour = std::make_unique<PatrolBehaviour>();
        botBehaviour->update(*this, dt, walls, gameMap, others);
    }

    if (wantToFire && canFire())
    {
        projectiles.push_back(fire());
    }
}

bool BotTank::canSeeTarget(const std::vector<Wall>& walls) const
{
    if (!target || !target->isAlive()) return false;

    const float visionRadius = 250.0f;
    Vector2D toTarget = target->getCenter() - getCenter();

    if (toTarget.length() > visionRadius) return false;

    return hasLineOfSight(getCenter(), target->getCenter(), walls);
}

 