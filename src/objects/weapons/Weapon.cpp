#include "Weapon.hpp"

void Weapon::Update(float deltaTime){
    for(Bullet* bullet : bullets){
        bullet->Update();
    }
    currentCooldown -= deltaTime;
}