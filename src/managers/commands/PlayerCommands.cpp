#include "PlayerCommands.hpp"

MoveLeft::MoveLeft(Player* player) : p(player){
    inputMode = InputMode::Continuous;
}

void MoveLeft::execute(){
    p->MoveLeft();
}

MoveRight::MoveRight(Player* player) : p(player){
    inputMode = InputMode::Continuous;
}

void MoveRight::execute(){
    p->MoveRight();
}

Fire::Fire(Player *player) : p(player){
    inputMode = InputMode::Continuous;
}

void Fire::execute(){
    p->Fire();
}

Stop::Stop(Player *player) : p(player) {
    inputMode = InputMode::Single;
}

void Stop::execute(){
    p->Stop();
}