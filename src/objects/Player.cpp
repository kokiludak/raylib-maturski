#include "Player.hpp"
#define ACCELERATION 10000.0

Player::Player(Vector2 pos) : RigidBody(RigidBodyParams { .maxSpeedX = 700.f}){
    position = pos;
}


void Player::MoveLeft(){
    acceleration.x = -ACCELERATION;
}
void Player::MoveRight(){
    acceleration.x = ACCELERATION;
}
void Player::Stop(){
    acceleration.x = 0;
}