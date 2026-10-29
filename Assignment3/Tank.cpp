#include "Tank.h"


Tank::Tank(Vector2D startPos, float speed, int health=100)
	: tankCenter(startPos), speed(speed), health(health) {}
int Tank::getSize() const { return size; }
int Tank::getHealth() const { return health; }
Vector2D Tank::getTankCenter() const { return tankCenter; }
Vector2D Tank::getDirection() const { return direction; }
bool Tank::isAlive() const { return health > 0; }


void Tank::takeDamage(int takenDamage)
{
	health -= takenDamage;	
}
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
	return Projectile(spawnPos, direction, this);
}
