#include "PlayerTank.h"
#include "BoxCollider.h"
#include <algorithm>



bool PlayerTank::isAlive() const { return health > 0; }


void PlayerTank::handleInput()
{
    Vector2D dir(0.0f, 0.0f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W)) dir.setY(dir.getY() - 1.0f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S)) dir.setY(dir.getY() + 1.0f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)) dir.setX(dir.getX() - 1.0f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)) dir.setX(dir.getX() + 1.0f);


    direction = dir;
}

void PlayerTank::move(float dt, const std::vector<Wall>& walls, const GameMap& gameMap)
{
    if (direction.getX() == 0.0f && direction.getY() == 0.0f)
    {
        return;
    }

    float speedModifier = gameMap.getSpeedModifier(tankCenter);
    float moveDistance = speed * speedModifier * dt;
    float halfSize = static_cast<float>(size) / 2.0f;

    float mapWidthPx = static_cast<float>(gameMap.getWidth()) * gameMap.getTileSize();
    float mapHeightPx = static_cast<float>(gameMap.getHeight()) * gameMap.getTileSize();

   
    float nextX = tankCenter.getX() + direction.getX() * moveDistance;
    nextX = std::clamp(nextX, halfSize, mapWidthPx - halfSize);

    
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
    nextY = std::clamp(nextY, halfSize, mapHeightPx - halfSize);

    Vector2D potentialTopLeftY(tankCenter.getX() - halfSize, nextY - halfSize);
    BoxCollider colY(potentialTopLeftY, static_cast<float>(size), static_cast<float>(size));

    bool collideY = false;
    for (const auto& wall : walls)
    {
        if (colY.intersects(wall.getCollider()))
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