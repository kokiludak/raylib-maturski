#include "PhysicsHandler.hpp"

bool PhysicsHandler::ShouldCollide(const RigidBody* a, const RigidBody* b)  const {
    return (a->collider.layer & b->collider.mask);
}

void PhysicsHandler::Update(float deltaTime){
    for(RigidBody* body : bodies){
        body->ApplyPhysics(deltaTime);
    }

    ResolveCollisions();
}

void PhysicsHandler::ResolveCollisions(){
    for(unsigned int i = 0; i < bodies.size(); ++i){
        for(unsigned int j = 0; j < bodies.size(); ++j){
            if(i == j) continue;
            RigidBody* a = bodies[i];
            RigidBody* b = bodies[j];

            if(!ShouldCollide(a, b)) continue;

            if(a->Collides(b)){
                
            }
        }
    }
}