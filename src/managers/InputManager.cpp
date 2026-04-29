#include "InputManager.hpp"
#include <raylib.h>

#define LEFT KEY_A
#define RIGHT KEY_D
#define FIRE KEY_SPACE

void InputManager::setLeft(Command* c) {left = c; }
void InputManager::setRight(Command* c) {right = c; }
void InputManager::setFire(Command* c) {fire = c; }
void InputManager::setStop(Command* c) {stop = c; }

std::vector<Command*> InputManager::handleInput(){
    std::vector<Command*> commands;
    if(left){
        if(IsKeyPressed(LEFT) && left->inputMode == InputMode::Single) commands.emplace_back(left);
        else if(IsKeyDown(LEFT) && left->inputMode == InputMode::Continuous) commands.emplace_back(left);
        else if(IsKeyReleased(LEFT)) commands.emplace_back(stop);
    }
    if(right){
        if(IsKeyPressed(RIGHT) && right->inputMode == InputMode::Single) commands.emplace_back(right);
        else if(IsKeyDown(RIGHT) && right->inputMode == InputMode::Continuous) commands.emplace_back(right);
        else if(IsKeyReleased(RIGHT)) commands.emplace_back(stop);
    }
    if(fire){
        if(IsKeyPressed(FIRE) && fire->inputMode == InputMode::Single) commands.emplace_back(fire);
        else if(IsKeyDown(FIRE) && fire->inputMode == InputMode::Continuous) commands.emplace_back(fire);
    }
    return commands;
};
