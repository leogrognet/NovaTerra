#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"

class Game {
private:
    RenderWindow window;
public:
    Game();
    ~Game();
    void run();
};
#endif