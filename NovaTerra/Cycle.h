#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Cycle {
public:
    enum class State {
        Day,
        Night
    };

    Cycle();
    ~Cycle();

    void changeState();
    void displayState();

private:
    State currentState;
};