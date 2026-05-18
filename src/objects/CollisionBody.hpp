#pragma once
#include "GameObject.hpp"
#include "Collision.hpp"

class CollisionBody : public GameObject {
public:
    Collider collider;
    virtual void OnCollision(const CollisionBody* other) {}
    bool Collides(const CollisionBody* other) const;
};