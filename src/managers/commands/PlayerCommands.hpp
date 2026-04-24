#pragma once
#include "../InputManager.hpp"
#include "../../objects/Player.hpp"
class MoveLeft : public Command {
public:
    MoveLeft(Player *p);
    void execute() override;
private:
    Player* p;
};

class MoveRight : public Command {
public:
    MoveRight(Player *p);
    void execute() override;
private:
    Player* p;
};

class Fire : public Command{
public:
    Fire(Player *p);
    void execute() override;
private:
    Player* p;
};

class Stop : public Command {
public:
    Stop(Player *p);
    void execute() override;
private:
    Player* p;
};