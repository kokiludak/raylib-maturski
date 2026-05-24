#pragma once
#include "../CollisionBody.hpp"
#include "../TexturedObject.hpp"
class Wall : public CollisionBody, public TexturedObject {
public:
    static constexpr const char* texturePath = "res/textures/wall.png";
    static constexpr const float width = 100, height = 1000;
    Wall(Vector2 pos) : TexturedObject(texturePath){
        SetTransform(Rectangle{pos.x, pos.y, width, height});
        collider.layer = LAYER_WALL;
    }
    void Draw() override;
};