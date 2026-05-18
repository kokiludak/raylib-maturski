#include "CollisionBody.hpp"

bool CollisionBody::Collides(const CollisionBody* other) const {
    return CheckCollisionRecs(this->transform, other->GetTransform());
}