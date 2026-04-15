#include "RigidBody.hpp"

RigidBody::RigidBody(const RigidBodyParams& params)
    : gravityScale(params.gravityScale),
      maxSpeedX(params.maxSpeedX),
      maxSpeedY(params.maxSpeedY)
{

}

void RigidBody::ApplyPhysics(float deltaTime) {
    velocity.x += acceleration.x * deltaTime;
    velocity.y += acceleration.y * deltaTime;

    if(velocity.x > maxSpeedX) velocity.x = maxSpeedX;
    if(velocity.x < -maxSpeedX) velocity.x = -maxSpeedX;

    if(velocity.y > maxSpeedY) velocity.y = maxSpeedY;
    if(velocity.y < -maxSpeedY) velocity.y = -maxSpeedY;
    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;
}

void RigidBody::Update(float deltaTime) {
    PreUpdate(deltaTime);
    ApplyPhysics(deltaTime);
    PostUpdate(deltaTime);
}

