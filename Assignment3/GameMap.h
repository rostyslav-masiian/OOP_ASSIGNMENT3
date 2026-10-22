#pragma once
#include <vector>

enum TerrainType
{
	Ground, 
	Mud
};
class GameMap
{
	protected:
		int size;
		std::vector<TerrainType> terrain;
};

