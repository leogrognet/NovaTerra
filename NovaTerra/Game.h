#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "Map.h"
#include "Scroll.h"
#include "Background.h"
#include "PlateformeTemp.h"
#include "MovingPlatform.h"

class Game {
private:
    const int WIDTH;
    const int HEIGHT;
    RenderWindow window;
public:
    Game(const int _WIDTH, const int _HEIGHT);
    ~Game();
    void run();
};
#endif