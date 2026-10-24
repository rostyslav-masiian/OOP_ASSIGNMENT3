#include "GameMap.h"
#include <random>

GameMap::GameMap(int width, int height, float tileSize, int defaultType)
	: width(width), height(height), tileSize(tileSize)
{
	grid.resize(height, std::vector<TileType>(width, TileType::Ground));

	static std::random_device rd;
	static std::mt19937 rng{ rd() };
	std::uniform_int_distribution<int> chance(1, 100);

	const int mudPercentage = 15;

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			
			if (x > 0 && x < width - 1 && y > 0 && y < height - 1)
			{
				if (chance(rng) <= mudPercentage)
				{
					grid[y][x] = TileType::Mud;
				}
				else
				{
					grid[y][x] = TileType::Ground;
				}
			}
			else
			{
				grid[y][x] = TileType::Ground;
			}
		}
	}
}

int GameMap::getHeight() const { return height; }
int GameMap::getWidth() const { return width; }
float GameMap::getTileSize() const { return tileSize; }


TileType GameMap::getTile(int x, int y) const
{
	if (x >= 0 && x < width && y >= 0 && y < height)
	{
		return grid[y][x];
	}
	return TileType::Ground;
}

bool GameMap::isMudZone(Vector2D position) const
{
	int tileX = static_cast<int>(position.getX() / tileSize);
	int tileY = static_cast<int>(position.getY() / tileSize);

	if (tileX >= 0 && tileX < width && tileY >= 0 && tileY < height)
	{
		return grid[tileY][tileX] == TileType::Mud;
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