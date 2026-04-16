#pragma once
#include "GameObject.hpp"

using CollisionLayer = int;
constexpr CollisionLayer LAYER_DEFAULT = 1 << 0;
constexpr CollisionLayer LAYER_PLAYER = 1 << 1;
constexpr CollisionLayer LAYER_ENEMY = 1 << 2;
constexpr CollisionLayer LAYER_WALL = 1 << 3;

struct Collider {
    Rectangle area;
    CollisionLayer layer = LAYER_DEFAULT;
    CollisionLayer mask = 0;
};

struct RigidBodyParams {
    float maxSpeedX = 300.0f;
    float maxSpeedY = 800.0f;
    float gravityScale = 1.0f;
};

class RigidBody : public GameObject {
public:
    explicit RigidBody(const RigidBodyParams& params = {});
    void Update(float deltaTime) override;
    void ApplyPhysics(float deltaTime);
    Collider collider;
    bool Collides(const RigidBody* other) const;
protected:
    static const float globalGravity;
    float gravityScale;
    Vector2 velocity {0, 0};
    Vector2 acceleration {0, 0};

    float maxSpeedX;
    float maxSpeedY;

    virtual void PreUpdate(float) {}
    virtual void PostUpdate(float) {}
};