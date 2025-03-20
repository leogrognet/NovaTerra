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

    void changeState();
    void displayState();

private:
    State currentState;
};