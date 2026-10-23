#include "Wall.h"


Wall::Wall(int gridX, int gridY, float tileSize) 
	: width(tileSize), height(tileSize), position(static_cast<float>(gridX* tileSize), static_cast<float>(gridY* tileSize)) {}

int Wall::getHealth() const { return health; }
Vector2D Wall::getPosition() const { return position; }

void Wall::takeDamage(int amount) 
{
	health -= amount; 
}
