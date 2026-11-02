#pragma once
#include "Vector2D.h"
#include "BoxCollider.h"
#include "Damageable.h"
class Wall : public Damageable
{
protected: 
	float width;
	float height;
	Vector2D position;
public:
	Wall(int gridX, int gridY, float tileSize, int health= 50);
	float getWidth() const;
	float getHeight() const;
	Vector2D getCenter() const override;
	Vector2D getPosition() const;
	BoxCollider getCollider() const;
};

