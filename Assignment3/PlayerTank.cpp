#include "PlayerTank.h"
#include "BoxCollider.h"
#include <algorithm>



bool PlayerTank::isAlive() const { return health > 0; }

PlayerTank::PlayerTank(Vector2D startPos, float speed, int health)
    : Tank(startPos, speed, health) {}

void PlayerTank::handleInput()
{
    Vector2D dir(0.0f, 0.0f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W)) dir.setY(dir.getY() - 1.0f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S)) dir.setY(dir.getY() + 1.0f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)) dir.setX(dir.getX() - 1.0f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)) dir.setX(dir.getX() + 1.0f);

    float len = std::sqrt(dir.getX() * dir.getX() + dir.getY() * dir.getY());

    if (len > 0.0f)
    {
        this->direction = Vector2D(dir.getX() / len, dir.getY() / len);
    }
}



void PlayerTank::move(float dt, const std::vector<Wall>& walls, const GameMap& gameMap)
{
    
    handleInput();

    
    Vector2D moveDir(0.0f, 0.0f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W)) moveDir.setY(moveDir.getY() - 1.0f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S)) moveDir.setY(moveDir.getY() + 1.0f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)) moveDir.setX(moveDir.getX() - 1.0f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)) moveDir.setX(moveDir.getX() + 1.0f);

    float len = std::sqrt(moveDir.getX() * moveDir.getX() + moveDir.getY() * moveDir.getY());

    
    if (len == 0.0f)
    {
        return;
    }

   
    moveDir = Vector2D(moveDir.getX() / len, moveDir.getY() / len);

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
    for (const auto& wall : walls)
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
    for (const auto& wall : walls)
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