#pragma once
class Vector2D
{
private:
	float x;
	float y;
public:
	Vector2D(float _x, float _y) : x(_x), y(_y) {}

	float getX() const { return x; }
	float getY() const { return y; }

	void setX(float newX) { x = newX; }
	void setY(float newY) { y = newY; }
};

