#include "RigidBody.hpp"

const float RigidBody::globalGravity = 1000.0f;
RigidBody::RigidBody(const RigidBodyParams& params)
    : gravityScale(params.gravityScale),
      maxSpeedX(params.maxSpeedX),
      maxSpeedY(params.maxSpeedY)
{

}

void RigidBody::ApplyPhysics(float deltaTime) {
    acceleration.y = globalGravity * gravityScale;
    velocity.x += acceleration.x * deltaTime;
    velocity.y += acceleration.y * deltaTime;

    if(velocity.x > maxSpeedX) velocity.x = maxSpeedX;
    if(velocity.x < -maxSpeedX) velocity.x = -maxSpeedX;

    if(velocity.y > maxSpeedY) velocity.y = maxSpeedY;
    if(velocity.y < -maxSpeedY) velocity.y = -maxSpeedY;
    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;
}

/*
tretiram poziciju predmeta kao sredinu predmeta.
racunam za sada da ce mi svi collideri u igrici biti pravougaonici,,
da bi sebi malo olaksao posao.
mozda postoji pametniji nacin da uradim ovu tranzlaciju u prostoru,
mozda i treba da krenem da pisem helper biblioteku za ovakve operacije.
posle cu mozda da ih ekstraktujem ako bude bilo dovoljno ovakvog cimanja.
*/

//VEC POSTOJI CHECKCOLLISION ZA RECTANGLES!!!!
bool RigidBody::Collides(const RigidBody* other) const {

    if(position.x - collider.area.width/2 > other->position.x + other->collider.area.width/2 || position.x + collider.area.width/2 < other->position.x - other->collider.area.width/2) return false;
    if(position.y - collider.area.height/2 > other->position.y + other->collider.area.height/2 || position.y + collider.area.height/2 < other->position.y - other->collider.area.width/2) return false;
    return true;
}

