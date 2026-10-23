#include "Projectile.h"
#include "Tank.h"

Projectile::Projectile(Vector2D direction, Vector2D projCenter, Tank* owner) 
	: direction(direction), projCenter(projCenter), owner(owner) {}


Vector2D Projectile::getCenter() const { return projCenter; }

int Projectile::getDamage() const { return damage; }
float Projectile::getRadius() const { return radius; }
float Projectile::getSpeed() const { return speed; }
bool Projectile::isExpired() { return lifespan <= 0; }

CircleCollider Projectile::getCollider() const { return CircleCollider(projCenter, radius); }

void Projectile::move(float dt)
{
	projCenter.setX(projCenter.getX() + direction.getX() * speed * dt);
	projCenter.setY(projCenter.getY() + direction.getY() * speed * dt);


	lifespan -= dt;
}


