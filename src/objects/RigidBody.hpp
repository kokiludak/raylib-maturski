#pragma once
#include "GameObject.hpp"

struct RigidBodyParams {
    float maxSpeedX = 300.0f;
    float maxSpeedY = 800.0f;
    float gravityScale = 1.0f;
};

class RigidBody : public GameObject {
public:
    explicit RigidBody(const RigidBodyParams& params = {});
    void Update(float deltaTime) override;
protected:
    static float globalGravity;
    float gravityScale;
    Vector2 velocity {0, 0};
    Vector2 acceleration {0, 0};

    float maxSpeedX;
    float maxSpeedY;
    
    virtual void PreUpdate(float) {}
    virtual void PostUpdate(float) {}
private:
    void ApplyPhysics(float deltaTime);
};