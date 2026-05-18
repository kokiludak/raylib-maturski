#pragma once
#include "../RigidBody.hpp"
#include "../Player.hpp"

struct EnemyParams{
    int hp = 4;
    RigidBodyParams rigidBody;
};

class Enemy : public RigidBody {
public:
    virtual ~Enemy() = default;
    Enemy(Player* player, const EnemyParams& params);
    void Update(float deltaTime) override;
    virtual void AI(float deltaTime) = 0;
    void OnCollision(const CollisionBody* other) override;
protected:
    Player* player;
private:
    void onDeath();
    int hp;
};