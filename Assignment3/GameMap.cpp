#include "GameMap.h"
#include <random>

GameMap::GameMap(int width = 20, int height = 20, float titleSize = 10.0f, int mudPercentage = 15) : width(width), height(height), tileSize(tileSize)
{
	grid.resize(height, std::vector<TileType>(width, TileType::Ground));


	std::random_device rd;
	std::mt19937 gen(rd);
	std::uniform_int_distribution<int> chance(1, 100);

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (chance(gen) <= mudPercentage)
			{
				grid[y][x] = TileType::Mud;
			}
			else
			{
				grid[y][x] = TileType::Ground;
			}
		}
	}
}

bool GameMap::isMudZone(Vector2D position) const
{
	int tileX = static_cast<int>(position.getX() / tileSize);
	int tileY = static_cast<int>(position.getY() / tileSize);

	bool inArray = tileX >= 0 && tileX < width && tileY >= 0 && tileY < height;
	if (inArray)
	{
		if (grid[tileY][tileX] == TileType::Mud)
		{
			return true;
		}
	}
	return false;
}

float GameMap::getSpeedModifier(Vector2D position) const
{
	if (isMudZone(position))
	{
		return 0.5f;
	}
	return 1.0f;
}