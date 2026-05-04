#include "Weapon.hpp"

void Weapon::Update(float deltaTime){
    currentCooldown -= deltaTime;
}

void Weapon::CoolDown(){
    currentCooldown = cooldownTime;
}