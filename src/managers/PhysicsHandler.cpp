#include "PhysicsHandler.hpp"

void PhysicsHandler::RegisterBody(RigidBody* body){
    bodies.emplace_back(body);
}

void PhysicsHandler::RegisterCollider(CollisionBody* collider){
    colliders.emplace_back(collider);
}
//najjace da mozes da uradis unregister ako imas vector... to ti dodje n^2 tj posto ti nije bitan redosled moze u n.

bool PhysicsHandler::ShouldCollide(const RigidBody* a, const CollisionBody* b)  const {
    return (a->collider.mask & b->collider.layer);
}

void PhysicsHandler::Update(float deltaTime){
    for(RigidBody* body : bodies){
        body->ApplyPhysics(deltaTime);
    }

    ResolveCollisions();
}

void PhysicsHandler::ResolveCollisions(){
    for(unsigned int i = 0; i < bodies.size(); ++i){
        //check against bodies...
        for(unsigned int j = 0; j < bodies.size(); ++j){
            if(i == j) continue;
            RigidBody* a = bodies[i];
            RigidBody* b = bodies[j];

            if(!ShouldCollide(a, b)) continue;

            if(a->Collides(b)){
                ResolveCollision(a, b);
                a->onCollision(b);
            }
        }
        //check against colliders(...staticbodies)
        for(unsigned int j = 0; j < colliders.size(); ++j){
            RigidBody* a = bodies[i];
            CollisionBody* b = colliders[j];
            if(!ShouldCollide(a, b)) continue;
            ResolveCollision(a, b);
        }
    }
}

/*
mozda je problem sto prvo proveravam a->b pa onda b->a.
ako se a nalazi u listi pre b, onda ce a biti izbaceno iz b.
ako se b nalazi u listi pre a, onda ce b biti izbaceno iz a.
zelim da proveram odvojeno zato sto mi je onda lakse da koristim
layer i masks zapravo. ako proveravam i masku od a prema layer od b,
i masku od b prema layer od a, onda ne znam zapravo ko zeli sa kim da
colliduje.... ajde videcu posle.

takodje ovde ima dosta ponavljanja 
*/



void PhysicsHandler::ResolveCollision(RigidBody* a, CollisionBody* b){
    Vector2 aPos = a->GetPosition();
    Vector2 bPos = b->GetPosition();
    //right edge
    if(aPos.x + a->collider.area.width/2 > bPos.x - b->collider.area.width/2){
        a->SetPosition({bPos.x - b->collider.area.width/2 - a->collider.area.width/2, aPos.y});
    }
    //left edge
    else {
        a->SetPosition({bPos.x + b->collider.area.width/2 + a->collider.area.width/2, aPos.y});
    }

    aPos = a->GetPosition();
    if(aPos.y + a->collider.area.height/2 > bPos.y - b->collider.area.height/2){
        a->SetPosition({aPos.x, bPos.y - b->collider.area.height/2 - a->collider.area.height/2});
    }
    else{
        a->SetPosition({aPos.x, bPos.y + b->collider.area.height/2 + a->collider.area.height/2});
    }
}