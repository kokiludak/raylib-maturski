#pragma once
#include "GameObject.hpp"
#include <raylib.h>
class StaticBody : public GameObject {
public:
    Rectangle collider;
};