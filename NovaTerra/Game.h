#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Menu.h"
#include "Map.h"

class Game {
private:
    RenderWindow window;
	Menu menu;
    Map* map;
    bool isPlaying;

public:
    Game();
    ~Game();
    void run();
    void handleEvents();
    void update();
    void render();
};
#endif