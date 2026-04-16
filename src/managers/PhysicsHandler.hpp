#pragma once
#include "../objects/RigidBody.hpp"
#include <vector>

class PhysicsHandler {
public:
    void Register(RigidBody *body);
    void UnRegister(RigidBody *body);

    void Update(float deltaTime);

private:
    std::vector<RigidBody*> bodies;

    void ResolveCollisions();
    bool ShouldCollide(const RigidBody* a, const RigidBody *b) const;
    void ResolveCollision(RigidBody* a, RigidBody *b);
};