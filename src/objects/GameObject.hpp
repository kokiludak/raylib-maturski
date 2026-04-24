#pragma once
#include <raylib.h>
class GameObject {
public:
    Vector2 GetPosition() const { return {transform.x, transform.y}; }
    Rectangle GetTransform() const { return transform; }
    void SetPosition(const Vector2 pos) {
        transform.x = pos.x;
        transform.y = pos.y;
    }
    void SetTransform(const Rectangle transform){
        this->transform = transform;
    }
    void Translate(const Vector2 delta){
        transform.x += delta.x;
        transform.y += delta.y;
    }

    /*
    ovo ce mozda postati muljavo tako ta treba uskoro da odlucim kako cu da se bavim koordinatama
    ima smisla da mi transform ostane u topleft formi i da bude izvor apsolutne istine,
    a da imam funkcije koje se bave ovim korisnim transformacijama koje ce samo meni licno 
    biti korisne...
    */
    Vector2 GetCenter() const {
        return {transform.x + transform.width * 0.5f, transform.y + transform.height * 0.5f};
    }

    void SetCenter(Vector2 center) {
        transform.x = center.x - transform.width * 0.5f;
        transform.y = center.y - transform.height * 0.5f;
    }
    
    virtual ~GameObject() = default;
    virtual void Update(float deltaTime) {}
protected:
    Rectangle transform;
};