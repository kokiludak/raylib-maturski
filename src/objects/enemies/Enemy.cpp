#include "Enemy.hpp"
#include <iostream>
Enemy::Enemy(Player* player, 
                const EnemyParams& params)
        : RigidBody(params.rigidBody),
        player(player),
        hp(params.hp)
{
    collider.layer = LAYER_ENEMY;
    collider.mask = LAYER_PLAYER | LAYER_FRIENDLY_PROJECTILE | LAYER_WALL;
}

void Enemy::onDeath(){
    alive = false;
}

void Enemy::Update(float deltaTime){
    if(hp <= 0){
        onDeath();
    }
    else AI(deltaTime);
}

void Enemy::OnCollision(const CollisionBody* other){
    if(other->collider.layer == LAYER_PLAYER && other->GetCenter().y < GetPosition().y){
        onDeath();
    }
    else if(other->collider.layer == LAYER_FRIENDLY_PROJECTILE){
        hp--;
    }
}