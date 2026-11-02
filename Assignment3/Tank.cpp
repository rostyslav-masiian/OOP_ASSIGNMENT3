#include "Tank.h"


Tank::Tank(Vector2D startPos, float speed, int health)
	: Damageable(health), speed(speed), tankCenter(startPos) {}


int Tank::getSize() const { return size; }
Vector2D Tank::getDirection() const { return direction; }
Vector2D Tank::getCenter() const { return tankCenter; }
bool Tank::canFire()
{
	return timeSinceLastShot <= 0.0f;
}

void Tank::setTankCenter(const Vector2D& newCenter)
{
	tankCenter = newCenter;
}

void Tank::updateCooldown(float dt)
{
	if (timeSinceLastShot > 0.0f)
	{
		timeSinceLastShot -= dt;
	}
}

void Tank::resetCooldown()
{
	timeSinceLastShot = timeCooldown;
}

BoxCollider Tank::getCollider() const 
{
	float halfSize = static_cast<float>(size) / 2.0f;
	Vector2D topLeft(tankCenter.getX() - halfSize, tankCenter.getY() - halfSize);
	return BoxCollider(topLeft, static_cast<float>(size), static_cast<float>(size));
}

Projectile Tank::fire()
{
	resetCooldown();
	Vector2D fireDir = this->direction;

	
	if (std::abs(fireDir.getX()) < 0.001f && std::abs(fireDir.getY()) < 0.001f)
	{
		fireDir = Vector2D(0.0f, -1.0f);
	}

	float offset = (static_cast<float>(this->size) / 2.0f) + 8.0f;
	Vector2D spawnPos = this->tankCenter + (fireDir * offset);
	return Projectile(spawnPos, fireDir, getProjectileOwner());
}

bool Tank::collidesAt(const Vector2D& center, const std::vector<Wall>& walls, const std::vector<const Tank*>& others) const
{
	float halfSize = static_cast<float>(size) / 2.0f;
	BoxCollider box(Vector2D(center.getX() - halfSize, center.getY() - halfSize),
		static_cast<float>(size), static_cast<float>(size));

	for (const Wall& wall : walls)
	{
		if (!!wall.isAlive() && box.intersects(wall.getCollider()))
		{
			return true;
		}
	}

	for (const Tank* other : others)
	{
		if (other != nullptr && other != this && other->isAlive() &&
			box.intersects(other->getCollider()))
		{
			return true;
		}
	}
	return false;
}

void Tank::setDirection(const Vector2D& newDirection)
{
	direction = newDirection;
}

void Tank::tryMove(const Vector2D& dir, float dt, const std::vector<Wall>& walls, const std::vector<const Tank*>& others, const GameMap& gameMap)
{
	if (dir.length() == 0.0f) return;

	Vector2D moveDir = dir.normalized();
	float moveDistance = speed * gameMap.getSpeedModifier(tankCenter) * dt;
	float halfSize = static_cast<float>(size) / 2.0f;
	float mapWidthPx = static_cast<float>(gameMap.getWidth()) * gameMap.getTileSize();
	float mapHeightPx = static_cast<float>(gameMap.getHeight()) * gameMap.getTileSize();

	float nextX = std::clamp(tankCenter.getX() + moveDir.getX() * moveDistance,
		halfSize, mapWidthPx - halfSize);
	if (!collidesAt(Vector2D(nextX, tankCenter.getY()), walls, others))
	{
		tankCenter.setX(nextX);
	}

	float nextY = std::clamp(tankCenter.getY() + moveDir.getY() * moveDistance,
		halfSize, mapHeightPx - halfSize);
	if (!collidesAt(Vector2D(tankCenter.getX(), nextY), walls, others))
	{
		tankCenter.setY(nextY);
	}
}