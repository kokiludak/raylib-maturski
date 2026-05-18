#include "Enemy.hpp"

Enemy::Enemy(Player* player, 
                const EnemyParams& params)
        : RigidBody(params.rigidBody),
        player(player),
        hp(params.hp)
{
}

void Enemy::onDeath(){
    alive = false;
}

void Enemy::Update(float deltaTime){
    if(hp <= 0){
        onDeath();
    }
    AI(deltaTime);
}

void Enemy::OnCollision(const CollisionBody* other){
    if(other->collider.layer == LAYER_PLAYER && other->GetCenter().y > GetCenter().y){
        onDeath();
    }
}