#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "Map.h"
#include "Scroll.h"
#include "Background.h"
#include "Menu.h"
#include "GolemEnemy.h"
#include "Plateform.h"
#include "MovingPlatform.h"
#include "BouncingPlatform.h"
#include "KillerEnemy.h"
#include "VineLadder.h"
#include "Firecamp.h"
#include "Cycle.h"
#include "ClosingDoor.h"

class Game {
private:
    const int WIDTH;
    const int HEIGHT;

    MenuState menuState;
    MenuSettings settingsMenu;

    Menu menu;

    RectangleShape night;
    RenderWindow window;
    vector<shared_ptr<Texture>> textureListTest;
    TextureLoader loadertest;

    bool isMainMenu = true;

public:

    Game(const int _WIDTH, const int _HEIGHT);
    ~Game();
    void run();
    void processMenu();
    void processSettingsMenu();
};
#endif