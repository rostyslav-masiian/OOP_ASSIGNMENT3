#include "CircleCollider.h"
#include "BoxCollider.h"
#include <algorithm>


bool CircleCollider::intersectsWith(const CircleCollider& other) const
{
    float dx = center.getX() - other.center.getX();
    float dy = center.getY() - other.center.getY();
    float distSq = dx * dx + dy * dy;
    float rSum = radius + other.radius;
    return distSq <= (rSum * rSum);
}


bool CircleCollider::intersectsWith(const BoxCollider& other) const
{
    float closestX = std::clamp(center.getX(), other.getPosition().getX(), other.getPosition().getX() + other.getWidth());
    float closestY = std::clamp(center.getY(), other.getPosition().getY(), other.getPosition().getY() + other.getHeight());

    float distX = center.getX() - closestX;
    float distY = center.getY() - closestY;

    return (distX * distX + distY * distY) <= (radius * radius);
}