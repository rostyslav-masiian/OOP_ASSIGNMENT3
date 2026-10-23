#pragma once
#include "Collider.h"
#include "Vector2D.h"

class CircleCollider : public Collider
{
private:
    Vector2D center;
    float radius;

public:
    CircleCollider(Vector2D center, float radius) : center(center), radius(radius) {}

    Vector2D getCenter() const { return center; }
    float getRadius() const { return radius; }

    
    bool intersects(const Collider& other) const override 
    {
        
        return other.intersectsWith(*this);
    }

    bool intersectsWith(const CircleCollider& other) const override;
    bool intersectsWith(const BoxCollider& other) const override;
};