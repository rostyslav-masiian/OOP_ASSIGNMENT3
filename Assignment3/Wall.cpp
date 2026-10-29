#include "Wall.h"


Wall::Wall(int gridX, int gridY, float tileSize, int health) 
	: width(tileSize), height(tileSize), position(static_cast<float>(gridX* tileSize), static_cast<float>(gridY* tileSize)), health(health) {}

int Wall::getHealth() const { return health; }
Vector2D Wall::getPosition() const { return position; }
BoxCollider Wall::getCollider() const
{
    return BoxCollider(position, width, height);
}

void Wall::takeDamage(int amount) 
{
	health -= amount; 
}

bool Wall::isDestroyed() const { return health <= 0; }
