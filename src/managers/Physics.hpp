#pragma once
#include "../objects/RigidBody.hpp"
#include "../objects/CollisionBody.hpp"
#include <vector>

class Physics {
public:
    void RegisterBody( RigidBody* body);
    void UnRegisterBody( RigidBody* body);
    void RegisterCollider( CollisionBody* collider);
    void UnRegisterCollider( CollisionBody* collider);

    static bool CheckBox(Rectangle box, CollisionLayer mask);
    void Update(float deltaTime);

private:
    std::vector<RigidBody*> bodies;
    std::vector<CollisionBody*> colliders;
    void ResolveCollisions();
    bool ShouldCollide(const RigidBody* a, const CollisionBody *b) const;
    void ResolveCollision(RigidBody* a, CollisionBody *b);
};