#include "Physics.hpp"
#include <algorithm>
#include <raymath.h>
#include <iostream>
/*
Generalno ne znam koji me je demon obuzeo da pravim asimetricne kolizije,
kako to moze biti dobro, bog zna haha... mozda i nije toliko strasno ali\
stvarno nemam reci

*/


void Physics::RegisterBody(RigidBody* body){
    bodies.emplace_back(body);
}

void Physics::UnRegisterBody(RigidBody* body){
    bodies.erase(
        std::remove(bodies.begin(), bodies.end(), body),
        bodies.end()
    );
}

void Physics::RegisterCollider(CollisionBody* collider){
    colliders.emplace_back(collider);
}

void Physics::UnRegisterCollider(CollisionBody* collider){
    colliders.erase(
        std::remove(colliders.begin(), colliders.end(), collider),
        colliders.end()
    );
}

bool Physics::ShouldCollide(const CollisionBody* a, const CollisionBody* b)  const {
    return (a->collider.mask & b->collider.layer);
}

void Physics::Update(float deltaTime){
    for(RigidBody* body : bodies){
        body->isGrounded = false;
        body->ApplyPhysics(deltaTime);
        Rectangle bodyT = body->GetTransform();
        if(bodyT.x < minBound) body->Translate({minBound-bodyT.x, 0});
        if(bodyT.x + bodyT.width > maxBound) {
            body->Translate({-(bodyT.x + bodyT.width - maxBound), 0});
        }
    }

    ResolveCollisions();
}

void Physics::ResolveCollisions(){
    for(unsigned int i = 0; i < bodies.size(); ++i){
        //check against bodies...
        for(unsigned int j = 0; j < bodies.size(); ++j){
            if(i == j) continue;
            RigidBody* a = bodies[i];
            RigidBody* b = bodies[j];
            if(!ShouldCollide(a, b)) continue;

            if(a->Collides(b)){
                ResolveCollision(a, b);
                a->OnCollision(b);
            }
        }
        //check against colliders(...staticbodies)
        for(unsigned int j = 0; j < colliders.size(); ++j){
            RigidBody* a = bodies[i];
            CollisionBody* b = colliders[j];
            if(!ShouldCollide(a, b)) continue;
            if(a->Collides(b)){
                //std::cout << "collision\n";
                a->OnCollision(b);
                ResolveCollision(a, b);
            }
        }
    }

    //oprostite mi
    for(unsigned int i = 0; i < colliders.size(); ++i){
        for(unsigned int j = i+1; j < colliders.size(); ++j){
            CollisionBody* a = colliders[i];
            CollisionBody* b = colliders[j];

            if(!Collides(a, b)) continue;

            if(ShouldCollide(a, b)){
                std::cout << "zdravo\n";
                a->OnCollision(b);
            }
            if(ShouldCollide(b, a)){
                std::cout << "vozdra\n";
                b->OnCollision(a);
            }
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



void Physics::ResolveCollision(RigidBody* dynamicBody, CollisionBody* staticBody){
    Rectangle r1 = dynamicBody->GetTransform();
    Rectangle r2 = staticBody->GetTransform();

    float overlapLeft   = (r1.x + r1.width) - r2.x;
    float overlapRight  = (r2.x + r2.width) - r1.x;
    float overlapTop    = (r1.y + r1.height) - r2.y;
    float overlapBottom = (r2.y + r2.height) - r1.y;

    const float slop = 0.001f;
    float minX = std::min(overlapLeft, overlapRight);
    float minY = std::min(overlapTop, overlapBottom);

    if(minX < minY){
        if(overlapLeft == minX){
            dynamicBody->Translate( {-(overlapLeft + slop), 0});
        }
        else{
            dynamicBody->Translate({overlapRight + slop, 0});
        }
        dynamicBody->velocity.x = 0;
    }
    else{
        if(overlapTop == minY){
            //is grounded. mozda napravi probleme ako igrac frame perfect skace itd.
            dynamicBody->isGrounded = true;
            dynamicBody->Translate({0, -(overlapTop + slop)});       // push up (landing on ground)
        }
        else{
            dynamicBody->Translate({0, overlapBottom + slop});    // push down (hit ceiling)
        }
        dynamicBody->velocity.y = 0;
    }
}