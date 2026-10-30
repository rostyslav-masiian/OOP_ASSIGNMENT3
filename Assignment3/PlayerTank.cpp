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
    direction = Vector2D(std::cos(angle), std::sin(angle));
}

void PlayerTank::move(float dt, const std::vector<Wall>& walls, const GameMap& gameMap)
{
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)) angle -= turnSpeed * dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)) angle += turnSpeed * dt;
    handleInput();

    
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W))
    {
        return;
    }

    Vector2D moveDir = direction;

    float speedModifier = gameMap.getSpeedModifier(tankCenter);
    float moveDistance = speed * speedModifier * dt;
    float halfSize = static_cast<float>(size) / 2.0f;

    float mapWidthPx = static_cast<float>(gameMap.getWidth()) * gameMap.getTileSize();
    float mapHeightPx = static_cast<float>(gameMap.getHeight()) * gameMap.getTileSize();

    float nextX = tankCenter.getX() + moveDir.getX() * moveDistance;
    nextX = std::clamp(nextX, halfSize, mapWidthPx - halfSize);

    Vector2D potentialTopLeftX(nextX - halfSize, tankCenter.getY() - halfSize);
    BoxCollider colX(potentialTopLeftX, static_cast<float>(size), static_cast<float>(size));

    bool collideX = false;
    for (const Wall& wall : walls)
    {
        if (!wall.isDestroyed() && colX.intersects(wall.getCollider()))
        {
            collideX = true;
            break;
        }
    }
    if (!collideX)
    {
        tankCenter.setX(nextX);
    }

    float nextY = tankCenter.getY() + moveDir.getY() * moveDistance;
    nextY = std::clamp(nextY, halfSize, mapHeightPx - halfSize);

    Vector2D potentialTopLeftY(tankCenter.getX() - halfSize, nextY - halfSize);
    BoxCollider colY(potentialTopLeftY, static_cast<float>(size), static_cast<float>(size));

    bool collideY = false;
    for (const Wall& wall : walls)
    {
        if (!wall.isDestroyed() && colY.intersects(wall.getCollider()))
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