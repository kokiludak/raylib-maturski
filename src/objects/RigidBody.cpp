#include "RigidBody.hpp"
#include "raymath.h"
const float RigidBody::globalGravity = 2000.0f;
RigidBody::RigidBody(const RigidBodyParams& params)
    : gravityScale(params.gravityScale),
      maxSpeedX(params.maxSpeedX),
      maxSpeedY(params.maxSpeedY)
{

}

void RigidBody::ApplyPhysics(float deltaTime) {
    acceleration = {0, 0};
    AddAcceleration({0, globalGravity * gravityScale});
    while(!accelerations.empty()){
        acceleration += accelerations.top();
        accelerations.pop();
    }
    velocity.x += acceleration.x * deltaTime;
    velocity.y += acceleration.y * deltaTime;

    if(velocity.x > maxSpeedX) velocity.x = maxSpeedX;
    if(velocity.x < -maxSpeedX) velocity.x = -maxSpeedX;

    if(velocity.y > maxSpeedY) velocity.y = maxSpeedY;
    if(velocity.y < -maxSpeedY) velocity.y = -maxSpeedY;
    transform.x += velocity.x * deltaTime;
    transform.y += velocity.y * deltaTime;
}

void RigidBody::AddAcceleration(Vector2 accel){
    accelerations.push(accel);
}

/*
tretiram poziciju predmeta kao sredinu predmeta.
racunam za sada da ce mi svi collideri u igrici biti pravougaonici,,
da bi sebi malo olaksao posao.
mozda postoji pametniji nacin da uradim ovu tranzlaciju u prostoru,
mozda i treba da krenem da pisem helper biblioteku za ovakve operacije.
posle cu mozda da ih ekstraktujem ako bude bilo dovoljno ovakvog cimanja.
*/
