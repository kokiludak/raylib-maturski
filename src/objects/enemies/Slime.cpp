#include "Slime.hpp"
#include <raymath.h>

constexpr float ACCEL_SPEED = 200.0f;
void Slime::AI(float deltaTime){
    Vector2 direction = player->GetCenter() - GetCenter();
    direction = Vector2Normalize(direction);

    
    AddAcceleration(direction * ACCEL_SPEED);
}

void Slime::Draw(){
    Vector2 center = GetCenter();
    DrawCircle(center.x, center.y, GetTransform().width/2, RED);


    
    DrawLine(GetCenter().x, GetCenter().y, player->GetCenter().x, player->GetCenter().y, BLUE);
    DrawText(TextFormat("Accel xy: %f %f", acceleration.x, acceleration.y), GetCenter().x, GetCenter().y - 60, 12, RAYWHITE);
}
