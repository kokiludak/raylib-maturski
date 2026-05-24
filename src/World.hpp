#pragma once
#include <vector>
#include <queue>
#include <functional>
#include "objects/enemies/Enemy.hpp"
class GameObject;

class Player;

using EnemyFactory = std::function<void(Vector2 pos)>;

struct EnemyEntry {
    EnemySpawnInfo info;
    EnemyFactory factory;
};

class World {
public:
    World(float min_bound, float max_bound);
    void Init(Player* player){
        this->player = player;
    }
    void Update(float deltaTime);
    template<typename T> void Register();
private:
    void GenerateChunk(float yOffset);
    void SpawnPlatform(float x, float y);
    void SpawnEnemy(EnemySpawnInfo::Placement placement, Vector2 pos);
    void Cleanup();
    float min_bound, max_bound;

    //mozda treba da se napravi timer class sa callbackom ili nesto::)
    static constexpr float min_spawnTime = 3.0f, max_spawnTime = 6.0f;
    static constexpr int max_structures = 20;
    float spawnTime = min_spawnTime;
    float generatedUntil = 0.0f;
    Player* player;
    std::vector<EnemyEntry> enemyRegistry;
    std::queue<CollisionBody*> structures;
};