#include "Physics.hpp"
#include <algorithm>
#include <raymath.h>

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

bool Physics::ShouldCollide(const CollisionBody* a, const CollisionBody* b) const {
    return (a->collider.mask & b->collider.layer);
}

void Physics::Update(float deltaTime){
    for(RigidBody* body : bodies){
        body->isGrounded = false;
        body->ApplyPhysics(deltaTime);
        Rectangle bodyT = body->GetTransform();
        if(bodyT.x < minBound) body->Translate({minBound - bodyT.x, 0});
        if(bodyT.x + bodyT.width > maxBound) {
            body->Translate({-(bodyT.x + bodyT.width - maxBound), 0});
        }
    }

    ResolveCollisions();
}

void Physics::ResolveCollisions(){
    
    for(unsigned int i = 0; i < bodies.size(); ++i){
        for(unsigned int j = i+1; j < bodies.size(); ++j){
            RigidBody* a = bodies[i];
            RigidBody* b = bodies[j];

            if(!Collides(a, b)) continue;

            bool aHitsB = ShouldCollide(a, b);
            bool bHitsA = ShouldCollide(b, a);

            if(aHitsB && bHitsA){
                ResolveCollision(a, b);
            }
            else if(aHitsB){
                ResolveCollision(a, static_cast<CollisionBody*>(b));
            }
            else if(bHitsA){
                ResolveCollision(b, static_cast<CollisionBody*>(a));
            }

            if(aHitsB) a->OnCollision(b);
            if(bHitsA) b->OnCollision(a);
        }
    }

    for(unsigned int i = 0; i < bodies.size(); ++i){
        for(unsigned int j = 0; j < colliders.size(); ++j){
            RigidBody* a = bodies[i];
            CollisionBody* b = colliders[j];

            if(!Collides(a, b)) continue;

            bool aHitsB = ShouldCollide(a, b);
            bool bHitsA = ShouldCollide(b, a);

            if(aHitsB) ResolveCollision(a, b);

            if(aHitsB) a->OnCollision(b);
            if(bHitsA) b->OnCollision(a);
        }
    }

    for(unsigned int i = 0; i < colliders.size(); ++i){
        for(unsigned int j = i+1; j < colliders.size(); ++j){
            CollisionBody* a = colliders[i];
            CollisionBody* b = colliders[j];

            if(!Collides(a, b)) continue;

            if(ShouldCollide(a, b)) a->OnCollision(b);
            if(ShouldCollide(b, a)) b->OnCollision(a);
        }
    }
}

void Physics::ResolveCollision(RigidBody* a, RigidBody* b){
    Rectangle r1 = a->GetTransform();
    Rectangle r2 = b->GetTransform();

    float overlapLeft   = (r1.x + r1.width)  - r2.x;
    float overlapRight  = (r2.x + r2.width)  - r1.x;
    float overlapTop    = (r1.y + r1.height) - r2.y;
    float overlapBottom = (r2.y + r2.height) - r1.y;

    const float slop = 0.001f;
    float minX = std::min(overlapLeft, overlapRight);
    float minY = std::min(overlapTop,  overlapBottom);

    if(minX < minY){
        if(overlapLeft < overlapRight){
            a->Translate({-(overlapLeft  / 2.0f + slop), 0});
            b->Translate({ (overlapLeft  / 2.0f + slop), 0});
        } else {
            a->Translate({ (overlapRight / 2.0f + slop), 0});
            b->Translate({-(overlapRight / 2.0f + slop), 0});
        }
        std::swap(a->velocity.x, b->velocity.x);
    } else {
        if(overlapTop < overlapBottom){
            a->Translate({0, -(overlapTop    / 2.0f + slop)});
            b->Translate({0,  (overlapTop    / 2.0f + slop)});
        } else {
            a->Translate({0,  (overlapBottom / 2.0f + slop)});
            b->Translate({0, -(overlapBottom / 2.0f + slop)});
        }
        std::swap(a->velocity.y, b->velocity.y);
    }
}


void Physics::ResolveCollision(RigidBody* a, CollisionBody* b){
    Rectangle r1 = a->GetTransform();
    Rectangle r2 = b->GetTransform();

    float overlapLeft   = (r1.x + r1.width)  - r2.x;
    float overlapRight  = (r2.x + r2.width)  - r1.x;
    float overlapTop    = (r1.y + r1.height) - r2.y;
    float overlapBottom = (r2.y + r2.height) - r1.y;

    const float slop = 0.001f;
    float minX = std::min(overlapLeft, overlapRight);
    float minY = std::min(overlapTop,  overlapBottom);

    if(minX < minY){
        if(overlapLeft < overlapRight){
            a->Translate({-(overlapLeft  + slop), 0});
        } else {
            a->Translate({ (overlapRight + slop), 0});
        }
        a->velocity.x = 0;
    } else {
        if(overlapTop < overlapBottom){
            a->isGrounded = true;
            a->Translate({0, -(overlapTop    + slop)});
        } else {
            a->Translate({0,  (overlapBottom + slop)});
        }
        a->velocity.y = 0;
    }
}