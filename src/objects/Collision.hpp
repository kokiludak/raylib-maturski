#pragma once
using CollisionLayer = int;
constexpr CollisionLayer LAYER_DEFAULT = 1 << 0;
constexpr CollisionLayer LAYER_PLAYER = 1 << 1;
constexpr CollisionLayer LAYER_ENEMY = 1 << 2;
constexpr CollisionLayer LAYER_WALL = 1 << 3;

struct Collider {
    CollisionLayer layer = LAYER_DEFAULT;
    CollisionLayer mask = 0;
};
