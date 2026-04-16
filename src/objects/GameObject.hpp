#pragma once
#include <raylib.h>
class GameObject {
public:
    const Vector2& GetPosition() const { return position; }
    void SetPosition(const Vector2& pos) {position = pos; }
    virtual ~GameObject() = default;
    virtual void Update(float deltaTime) {}
protected:
    Vector2 position;
    float rotation;
};