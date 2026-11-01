#pragma once
#include <cstdint>

struct Color
{
	std::uint8_t r = 255;
	std::uint8_t g = 255;
	std::uint8_t b = 255;
	std::uint8_t a = 255;
};

namespace Palette
{

	constexpr Color Outline{ 0, 0, 0 };
	constexpr Color Ground{ 1, 66, 2 };
	constexpr Color Mud{ 110, 60, 20 };
	constexpr Color Wall{ 100, 100, 100 };
}