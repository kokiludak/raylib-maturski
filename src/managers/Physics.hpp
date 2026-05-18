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
    void SetBounds(int minBound, int maxBound){
        this->minBound = minBound;
        this->maxBound = maxBound;
    }
    static bool CheckBox(Rectangle box, CollisionLayer mask);
    void Update(float deltaTime);
    const int UPS = 120;
private:
    int minBound = INT_MIN, maxBound = INT_MAX;
    std::vector<RigidBody*> bodies;
    std::vector<CollisionBody*> colliders;
    void ResolveCollisions();
    bool ShouldCollide(const CollisionBody* a, const CollisionBody *b) const;
    void ResolveCollision(RigidBody* a, CollisionBody *b);
};