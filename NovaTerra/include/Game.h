#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Game {
private:
    sf::RenderWindow window;
public:
    Game();
    ~Game();
    void run();
};
#endif