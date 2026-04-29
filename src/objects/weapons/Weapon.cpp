#include "Weapon.hpp"

void Weapon::Update(float deltaTime){
    currentCooldown -= deltaTime;
}