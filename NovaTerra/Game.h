#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "Map.h"
#include "Scroll.h"
#include "World.h"

class Game {
private:
    const int WIDTH;
    const int HEIGHT;
    RenderWindow window;
    sf::RectangleShape bg;
    Map* map;
    //Scroll* scroll;
    World* world;
public:
    Game(const int _WIDTH, const int _HEIGHT);
    ~Game();
    void run();
};