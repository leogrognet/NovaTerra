#include "Cycle.h"

Cycle::Cycle() : currentState(State::Day) {}

Cycle::~Cycle() {}
void Cycle::changeState() {
    if (currentState == State::Day) {
        currentState = State::Night;
        std::cout << "Au dodo.\n";
    }
    else {
        currentState = State::Day;
        std::cout << "Debout.\n";
    }
}

void Cycle::displayState() {
    if (currentState == State::Day) {
        std::cout << "C'est actuellement le jour\n";
    }
    else {
        std::cout << "C'est actuellement la nuit\n";
    }
}