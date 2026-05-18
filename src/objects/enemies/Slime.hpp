#pragma once
#include "Enemy.hpp"

class Slime : public Enemy {
public:
    void AI(float deltaTime) override;
    void Draw() override;
    Slime(Player *p)
        : Enemy(p, {
            .hp = 4,
            .rigidBody = {
                .maxSpeedX = 120.0f,
                .maxSpeedY = 120.0f,
                .gravityScale = 0.0f
            }
        }) 
        {}
    
};