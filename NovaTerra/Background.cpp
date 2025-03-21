#include "Background.h"
#include <iostream>

Background::Background(const string& texturePath, float speed) : scrollSpeed(speed) {

    if (!texture.loadFromFile("../NovaTerra/assets/Image/BackGround/Fond_Biome_2.png")) {
        throw runtime_error("Failed to load texture");
    }

    float scaleX = 1920.f / texture.getSize().x;
    float scaleY = 1080.f / texture.getSize().y;

    sprite.setTexture(texture);
    sprite.setPosition(0, 0);
    sprite.setScale(scaleX, scaleY);

    sprite2.setTexture(texture);
    sprite2.setPosition(sprite.getGlobalBounds().width, 0);
    sprite2.setScale(scaleX, scaleY);
}

void Background::update(float deltaTime, Vector2f position) {
    float movementX = scrollSpeed * deltaTime; 
    float movementY = 0; 

    float offsetX = position.x*0.01;
    float offsetY = position.y;


    sprite.move(movementX, movementY);
    sprite2.move(movementX, movementY);


    sprite.setPosition(sprite.getPosition().x, position.y-500 );
    sprite2.setPosition(sprite2.getPosition().x, position.y-500 );


    if (sprite.getPosition().x + sprite.getGlobalBounds().width <= position.x - 500) {
        sprite.setPosition(sprite2.getPosition().x + sprite2.getGlobalBounds().width, sprite.getPosition().y);
    }
    if (sprite2.getPosition().x + sprite2.getGlobalBounds().width <= position.x - 960) {
        sprite2.setPosition(sprite.getPosition().x + sprite.getGlobalBounds().width, sprite2.getPosition().y);
    }
}


void Background::draw(RenderWindow& window) {
    window.draw(sprite);
    window.draw(sprite2);
}