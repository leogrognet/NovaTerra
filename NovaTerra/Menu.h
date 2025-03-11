#pragma once
#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Game.h"

using namespace std;
using namespace sf
;
enum class MenuState { MAIN, SETTINGS };

class Button {
public:
    Sprite sprite;

    Button(float x, float y, Texture& texture);
    bool isHovered(const Vector2f& mousePos);
};

class Menu {
private:
    RenderWindow& window;
    MenuState menuState;
    Texture backgroundTexture;
    Sprite background;
    vector<Button> mainMenu;
    vector<Button> settingsMenu;
public:
    Menu(RenderWindow& win);
    void handleEvent(const Event& event);
    void render();
};

#endif // MENU_H