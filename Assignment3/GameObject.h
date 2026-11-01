#pragma once
#include "Vector2D.h"

class GameObject
{
public:
	virtual ~GameObject() = default;

	virtual bool isAlive() const = 0;
	virtual Vector2D getCenter() const = 0;
};