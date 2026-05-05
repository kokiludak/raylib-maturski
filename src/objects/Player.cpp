#include "Player.hpp"
#include "../managers/Physics.hpp"
#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include <algorithm>

//zasto sam ovo stavio kao definition?
#define ACCELERATION 10000.0
#define JUMP_HEIGHT 1000.0
Player::Player(Vector2 pos) : RigidBody(RigidBodyParams { .maxSpeedX = 1500.f}){
    SetPosition(pos);
}

Player::Player(Rectangle transform) : RigidBody(RigidBodyParams {.maxSpeedX = 1500.f}){
    SetTransform(transform);
}

void Player::MoveLeft(){
    desiredMovement.x -= 1;
    Clamp(desiredMovement.x, -1, 1);
}
void Player::MoveRight(){
    desiredMovement.x += 1;
    Clamp(desiredMovement.x, -1, 1);
}

void Player::Fire(){
    if(isGrounded){
        std::cout<<"i am jump man\n";
        velocity.y = -JUMP_HEIGHT;
        weapon->CoolDown();
    }
    else if(weapon->Fire(GetCenter())) velocity.y = std::min(velocity.y, -weapon->GetRecoil());
}

void Player::Stop(){
    desiredMovement.x = 0;
}

void Player::Update(float deltaTime)  {
    acceleration.x = desiredMovement.x * ACCELERATION;

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



/*void Player::onCollision(const CollisionBody* other) {
    if(other->collider.layer == LAYER_WALL){
        std::cout<<"im ground man\n";
        isGrounded = true;
    }
}
nek ostane ovo ovde idejno.
pravilan redosled je input -> update -> physics -> render -> repeat.

*/