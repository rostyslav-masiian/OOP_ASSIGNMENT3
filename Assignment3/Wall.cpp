#include "Wall.h"


Wall::Wall(int gridX, int gridY, float tileSize, int health) 
	: width(tileSize), height(tileSize), position(static_cast<float>(gridX* tileSize), static_cast<float>(gridY* tileSize)), Damageable(health) {}

Vector2D Wall::getPosition() const { return position; }

float Wall::getWidth() const { return width; }
float Wall::getHeight() const { return height; }
Vector2D Wall::getCenter() const
{
	return Vector2D(position.getX() + width / 2.0f, position.getY() + height / 2.0f);
}
BoxCollider Wall::getCollider() const
{
    return BoxCollider(position, width, height);
}

