#include "World.hpp"

#include "objects/enemies/Slime.hpp"

#include "objects/structures/Wall.hpp"
#include "managers/SpawnEvent.hpp"
#include <raymath.h>
#include <iostream>
World::World(float min_bound, float max_bound) 
        : min_bound(min_bound),
        max_bound(max_bound)
{
    Register<Slime>();
}

template<typename T>
void World::Register(){
    enemyRegistry.push_back({
        T::SpawnInfo,
        [this](Vector2 pos) {
            SpawnBus::Spawn<T>(player, pos);
        }
    });
}


void World::SpawnEnemy(EnemySpawnInfo::Placement placement, Vector2 pos){
    std::vector<EnemyEntry*> candidates;
    for (auto& e : enemyRegistry){
        if(e.info.placement == placement){
            candidates.push_back(&e);
        }
    }
    float totalWeight = 0;
    for (auto* e : candidates) totalWeight += e->info.weight;
    float roll = GetRandomValue(0, 1000) / 1000.0f * totalWeight;
    for(auto* e : candidates){
        roll -= e->info.weight;
        if(roll <= 0){
            e ->factory(pos); return;
        }
    }
}

void World::Cleanup(){
    while(structures.size() > max_structures){
        structures.front()->alive = false;
        structures.pop();
    }
}

void World::GenerateChunk(float yOffset){
    structures.push(SpawnBus::Spawn<Wall>(Vector2{min_bound, yOffset}));
    structures.push(SpawnBus::Spawn<Wall>(Vector2{max_bound, yOffset}));

    generatedUntil += Wall::height;
}

void World::Update(float deltaTime){
    spawnTime -= deltaTime;
    if(spawnTime <= 0){
        float t = GetRandomValue(0, 1000) / 1000.0f;
        SpawnEnemy(EnemySpawnInfo::Placement::FLOATING, {Lerp(min_bound, max_bound, t), player->GetCenter().y + 300.0f});

        t = GetRandomValue(0, 1000) / 1000.0f;
        spawnTime = Lerp(min_spawnTime, max_spawnTime, t);
    }

    if(player->GetCenter().y + 1200.0f > generatedUntil){
        GenerateChunk(generatedUntil);
    }

    Cleanup();
}