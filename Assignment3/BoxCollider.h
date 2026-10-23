#pragma once
#include "Collider.h"
#include "Vector2D.h"

class BoxCollider : public Collider
{
private:
    Vector2D position; 
    float width;
    float height;

public:
    BoxCollider(Vector2D position, float width, float height) : position(position), width(width), height(height) {}

    Vector2D getPosition() const { return position; }
    float getWidth() const { return width; }
    float getHeight() const { return height; }

    bool intersects(const Collider& other) const override 
    {
        return other.intersectsWith(*this);
    }

    bool intersectsWith(const CircleCollider& other) const override;
    bool intersectsWith(const BoxCollider& other) const override;
};