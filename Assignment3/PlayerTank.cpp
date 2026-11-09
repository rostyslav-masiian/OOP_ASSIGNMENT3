#include "PlayerTank.h"
#include "BoxCollider.h"
#include <algorithm>



PlayerTank::PlayerTank(Vector2D startPos, float speed, int health)
    : Tank(startPos, speed, health)
{
    updateDirection();
}
ProjectileOwner PlayerTank::getProjectileOwner() const { return ProjectileOwner::Player; }


void PlayerTank::moveForward(float dt, const std::vector<Wall>& walls, 
    const GameMap& gameMap, const std::vector<const Tank*>& others)
{
    tryMove(getDirection(), dt, walls, others, gameMap);
}

void PlayerTank::turnLeft(float dt)
{
    angle -= turnSpeed * dt;

}
void PlayerTank::turnRight(float dt)
{
    angle += turnSpeed * dt;
}

void PlayerTank::updateDirection()
{
    setDirection(Vector2D(std::cos(angle), std::sin(angle)));
}


void PlayerTank::update(float dt, const std::vector<Wall>& walls, const GameMap& gameMap,
    const std::vector<const Tank*>& others,
    std::vector<Projectile>& projectiles)
{
    updateCooldown(dt);
    updateDirection();

}