#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "Map.h"
#include "Scroll.h"
#include "Background.h"
#include "GolemEnemy.h"
#include "Plateform.h"
#include "MovingPlatform.h"
#include "BouncingPlatform.h"
#include "VineLadder.h"
#include "Menu.h"

class Game {
private:
    const int WIDTH;
    const int HEIGHT;
	MenuState menuState;
	MenuSettings settingsMenu;
    Menu menu;
    RenderWindow window;
    vector<shared_ptr<Texture>> textureListTest;
    TextureLoader loadertest;

public:

    Game(const int _WIDTH, const int _HEIGHT);
    ~Game();
    void run();
	void processMenu();
	void processSettingsMenu();
};
#endif