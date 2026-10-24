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

	Vector2D operator+(const Vector2D& other) const 
	{
		return Vector2D(x + other.x, y + other.y);
	}

	Vector2D operator-(const Vector2D& other) const 
	{
		return Vector2D(x - other.x, y - other.y);
	}

	Vector2D operator*(float scalar) const 
	{
		return Vector2D(x * scalar, y * scalar);
	}

	float length() const 
	{
		return std::sqrt(x * x + y * y);
	}

	Vector2D normalized() const 
	{
		float len = length();
		if (len == 0.0f) return Vector2D(0.0f, 0.0f);
		return Vector2D(x / len, y / len);
	}
};

