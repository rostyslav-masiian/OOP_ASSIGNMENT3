#pragma once
#include <vector>

#include "Vector2D.h"

enum TileType
{
	Ground, 
	Mud
};
class GameMap
{
protected:
	int width = 20;
	int height = 20;
	float tileSize = 10.0f;
	int mudPercentage = 15;
	std::vector< std::vector<TileType>> grid;
public:
	GameMap(int width = 20, int height = 20, float titleSize = 10.0f, int mudPercentage = 15);
	bool isMudZone(Vector2D position) const;
	TileType getTile(int x, int y) const;
	float getSpeedModifier(Vector2D position) const;
	int getHeight() const;
	int getWidth() const;
	float getTileSize() const;
};

