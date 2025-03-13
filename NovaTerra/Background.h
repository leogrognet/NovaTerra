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
    Texture texture2;
    Sprite sprite;
    Sprite sprite2;

    //   palier pal;

    Background(const string& texturePath, float speed);
    void update(float deltaTime);
    void draw(RenderWindow& window);

};