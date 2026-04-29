#pragma once
#include <vector>

enum class InputMode { Continuous, Single};
class Command{
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
    InputMode inputMode;
};


class InputManager {
public:
    void setLeft(Command* c);
    void setRight(Command* c);
    void setStop(Command* c);
    void setFire(Command* c);
    std::vector<Command*> handleInput();
private:
    Command* left = nullptr;
    Command* right = nullptr;
    Command* fire = nullptr;
    Command* stop = nullptr;
};

