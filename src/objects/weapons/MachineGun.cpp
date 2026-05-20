#include "MachineGun.hpp"
#include <raylib.h>

void MachineGunBullet::Update(float deltaTime){
    Translate({0, velocity * deltaTime});
}

void MachineGunBullet::OnCollision(const CollisionBody* other){
    if(other->collider.layer != LAYER_PLAYER) alive = false;
}

MachineGunBullet::MachineGunBullet(float velocity) : velocity(velocity){
    collider.layer = LAYER_FRIENDLY_PROJECTILE;
    collider.mask = LAYER_WALL | LAYER_ENEMY;
    SetTransform({0, 0, 50, 50});
}

void MachineGunBullet::Draw(){
    Vector2 position = GetCenter();
    DrawCircle(position.x, position.y, GetTransform().width, RAYWHITE);
}

void MachineGun::OnFire(Vector2 position){
    MachineGunBullet* bullet = SpawnBus::Spawn<MachineGunBullet>(3000);
    bullet->SetCenter(position);
}
