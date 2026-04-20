#pragma once
#include "GameObject.hpp"
#include "Collision.hpp"
#include "CollisionBody.hpp"
struct RigidBodyParams {
    float maxSpeedX = 300.0f;
    float maxSpeedY = 800.0f;
    float gravityScale = 1.0f;
};

class RigidBody : public CollisionBody {
public:
    explicit RigidBody(const RigidBodyParams& params = {});
    void ApplyPhysics(float deltaTime);
    bool Collides(const CollisionBody* other) const;
    virtual void onCollision(const RigidBody* other) const {}

    //privremeno radim ovo...
    //izgleda da cu mozda trebati da napravim ceo mass i force system ali nadamo se da nece doci do toga...
    Vector2 velocity {0, 0};
protected:
    static const float globalGravity;
    float gravityScale;
    
    Vector2 acceleration {0, 0};

    float maxSpeedX;
    float maxSpeedY;
};