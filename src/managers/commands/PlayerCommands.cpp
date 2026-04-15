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

Stop::Stop(Player *player) : p(player) {
    inputMode = InputMode::Single;
}

void Stop::execute(){
    p->Stop();
}