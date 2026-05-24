#pragma once
#include "Enemy.hpp"
#include "../TexturedObject.hpp"

class Slime : public Enemy, public TexturedObject {
public:
    static constexpr const char* path = "res/textures/Slime.png";
    static constexpr EnemySpawnInfo SpawnInfo  = {
        EnemySpawnInfo::Placement::FLOATING,
        1.0f
    };
    void AI(float deltaTime) override;
    void Draw() override;
    Slime(Player *p, Vector2 pos)
        : Enemy(p, {
            .hp = 4,
            .rigidBody = {
                .maxSpeedX = 120.0f,
                .maxSpeedY = 120.0f,
                .gravityScale = 0.0f
            }
        }), TexturedObject(path) 
        {
            SetTransform({pos.x, pos.y, 100, 100});
        }
    
};