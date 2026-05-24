#pragma once
#include "../CollisionBody.hpp"
#include "../TexturedObject.hpp"

class Platform : public CollisionBody, public TexturedObject {
public:
    static constexpr const char* texturePath = "res/textures/platform.png";
    Platform(Rectangle transform) : TexturedObject(texturePath) {
        SetTransform(transform);
    }
    void Draw() override;
};