#include "BoxCollider.h"
#include "CircleCollider.h"


bool BoxCollider::intersectsWith(const CircleCollider& other) const
{
    return other.intersectsWith(*this);
}


bool BoxCollider::intersectsWith(const BoxCollider& other) const
{
    return (position.getX() < other.position.getX() + other.width &&
        position.getX() + width > other.position.getX() &&
        position.getY() < other.position.getY() + other.height &&
        position.getY() + height > other.position.getY());
}