#pragma once

class CircleCollider;
class BoxCollider;

class Collider
{
public:
	virtual ~Collider() = default;
	virtual bool intersects(const Collider& other) const = 0;
	virtual bool intersectsWith(const BoxCollider& other) const = 0;
	virtual bool intersectsWith(const CircleCollider& other) const = 0;

};