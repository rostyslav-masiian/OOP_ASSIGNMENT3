#include "Tank.h"

int Tank::getSize() const { return size; }
int Tank::getHealth() const { return health; }
Vector2D Tank::getTankCenter() const { return tankCenter; }
void Tank::takeDamage(int takenDamage)
{
	health -= takenDamage;	
}
bool Tank::canFire()
{
	return timeSinceLastShot <= 0.0f;
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
	
	return Projectile(tankCenter, direction, this);
}
