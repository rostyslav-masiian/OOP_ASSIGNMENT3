#include "Projectile.h"
#include "Tank.h"


Projectile::Projectile(Vector2D projCenter, Vector2D direction, ProjectileOwner ownerType)
	: projCenter(projCenter), direction(direction), ownerType(ownerType) {}



Vector2D Projectile::getCenter() const { return projCenter; }
Vector2D Projectile::getDirection() const { return direction; }

int Projectile::getDamage() const { return damage; }
float Projectile::getRadius() const { return radius; }
float Projectile::getSpeed() const { return speed; }
void Projectile::destroy() { destroyed = true; }
bool Projectile::isAlive() const { return !destroyed && lifespan > 0.0f; }
ProjectileOwner Projectile::getOwner() const { return ownerType; }

CircleCollider Projectile::getCollider() const { return CircleCollider(projCenter, radius); }


void Projectile::move(float dt)
{
	projCenter.setX(projCenter.getX() + direction.getX() * speed * dt);
	projCenter.setY(projCenter.getY() + direction.getY() * speed * dt);


	lifespan -= dt;
}


