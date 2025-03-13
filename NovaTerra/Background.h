#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdexcept>

using namespace std;
using namespace sf;

class Background {
private:
    float scrollSpeed;

public:
    Texture texture;
    Sprite sprite;
    Sprite sprite2;

    Background(const string& texturePath, float speed);
    void update(float deltaTime);
    void draw(RenderWindow& window);

};