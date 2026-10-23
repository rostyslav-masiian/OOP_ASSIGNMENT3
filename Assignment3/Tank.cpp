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
Projectile Tank::fire()
{
	
	return Projectile(tankCenter, direction, this);
}
