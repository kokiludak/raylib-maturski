#pragma once
#include "GameObject.hpp"
#include "Collision.hpp"

class CollisionBody : public GameObject {
public:
    Collider collider;
};