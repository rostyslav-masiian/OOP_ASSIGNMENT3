#include "PlayerTank.h"
#include "BoxCollider.h"
#include <algorithm>



PlayerTank::PlayerTank(Vector2D startPos, float speed, int health)
    : Tank(startPos, speed, health)
{
    handleInput();
}
ProjectileOwner PlayerTank::getProjectileOwner() const { return ProjectileOwner::Player; }


void PlayerTank::handleInput()
{
    setDirection(Vector2D(std::cos(angle), std::sin(angle)));
}

void PlayerTank::move(float dt, const std::vector<Wall>& walls, const GameMap& gameMap,
    const std::vector<const Tank*>& others)
{
    if (input.turnLeft)  angle -= turnSpeed * dt;
    if (input.turnRight) angle += turnSpeed * dt;
    handleInput();

    if (input.forward)
    {
        tryMove(getDirection(), dt, walls, others, gameMap);
    }
}

void PlayerTank::update(float dt, const std::vector<Wall>& walls, const GameMap& gameMap,
    const std::vector<const Tank*>& others,
    std::vector<Projectile>& projectiles)
{
    updateCooldown(dt);
    move(dt, walls, gameMap, others);

    if (input.fire && canFire())
    {
        projectiles.push_back(fire());
    }
}