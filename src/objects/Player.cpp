#include "Player.hpp"
#include "../managers/Physics.hpp"
#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include <algorithm>


constexpr float ACCELERATION = 10000.0;
constexpr float JUMP_HEIGHT = 1000.0;
constexpr float BOUNCE_HEIGHT = 400.0;

Player::Player(Vector2 pos) : RigidBody(RigidBodyParams { .maxSpeedX = 1500.f, .maxSpeedY = 4000.0f}){
    SetPosition(pos);
}

Player::Player(Rectangle transform) : RigidBody(RigidBodyParams {.maxSpeedX = 1500.f, .maxSpeedY = 4000.0f}){
    SetTransform(transform);
}

void Player::MoveLeft(){
    desiredMovement.x -= 1;
    Clamp(desiredMovement.x, -1, 1);
}
void Player::MoveRight(){
    desiredMovement.x += 1;
    desiredMovement.x = Clamp(desiredMovement.x, -1, 1);
}

void Player::Fire(){
    if(isGrounded){
        velocity.y = -JUMP_HEIGHT;
        if(weapon != nullptr) weapon->CoolDown();
    }
    else if(weapon != nullptr && weapon->Fire(GetCenter())) velocity.y = std::min(velocity.y, -weapon->GetRecoil());
}

void Player::Stop(){
    desiredMovement.x = 0;
}

void Player::Update(float deltaTime)  {

    currentInvulnerability -= deltaTime;
    AddAcceleration({desiredMovement.x * ACCELERATION, 0});

    if(isGrounded) weapon->Reload();
  
    //ne znam da li je ovo u redu da se radi ovako
    if(weapon != nullptr) weapon->Update(deltaTime);
    //fake drag
    if(desiredMovement.x == 0) velocity.x = Lerp(velocity.x, 0.0f, 20.0f * deltaTime);
    desiredMovement.x = 0;
    
}

void Player::Draw(){
    Rectangle transform = GetTransform();
    DrawRectangle(transform.x, transform.y, transform.width, transform.height, RAYWHITE);
}



void Player::OnCollision(const CollisionBody* other) {
    if(other->collider.layer == LAYER_ENEMY){
        if(GetCenter().y < other->GetPosition().y){
            velocity.y = -BOUNCE_HEIGHT;
            weapon->Reload();
        }
        else if(currentInvulnerability <= 0){
            hp--;
            currentInvulnerability = invulnerabilityTime;
        }
    }
}
