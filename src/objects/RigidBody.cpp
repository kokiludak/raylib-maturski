#include "RigidBody.hpp"

const float RigidBody::globalGravity = 1000.0f;
RigidBody::RigidBody(const RigidBodyParams& params)
    : gravityScale(params.gravityScale),
      maxSpeedX(params.maxSpeedX),
      maxSpeedY(params.maxSpeedY)
{

}

void RigidBody::ApplyPhysics(float deltaTime) {
    //acceleration.y = globalGravity * gravityScale;
    velocity.x += acceleration.x * deltaTime;
    velocity.y += acceleration.y * deltaTime;

    if(velocity.x > maxSpeedX) velocity.x = maxSpeedX;
    if(velocity.x < -maxSpeedX) velocity.x = -maxSpeedX;

    if(velocity.y > maxSpeedY) velocity.y = maxSpeedY;
    if(velocity.y < -maxSpeedY) velocity.y = -maxSpeedY;
    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;
}

bool RigidBody::Collides(const RigidBody* other) const {
    if(position.x > other->position.x + other->collider.area.width || position.x + collider.area.width < other->position.x) return false;
    if(position.y > other->position.y + other->collider.area.height || position.y + collider.area.height < other->position.y) return false;
    return true;
}

void RigidBody::Update(float deltaTime) {
    PreUpdate(deltaTime);
    ApplyPhysics(deltaTime);
    PostUpdate(deltaTime);
}

