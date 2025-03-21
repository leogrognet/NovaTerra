#include "Background.h"
#include <iostream>

Background::Background(const string& texturePath, float speed) : scrollSpeed(speed) {

    if (!texture.loadFromFile("../NovaTerra/assets/Image/BackGround/Fond_Biome_2.png")) {
        throw runtime_error("Failed to load texture");
    }

    float scaleX = (1920.f / texture.getSize().x) * 0.65f;
    float scaleY = (1080.f / texture.getSize().y) * 0.65f;




    auto sprite = make_shared<Sprite>();
    sprite->setTexture(texture);
    sprite->setPosition(0, 0);
    sprite->setScale(scaleX, scaleY);
    sprites.push_back(sprite);
    for (int i = 0; i < 5; i++) {
        auto sprite_t = make_shared<Sprite>();
        sprite_t->setTexture(texture);
        sprite_t->setPosition(sprites.back()->getGlobalBounds().width + sprites.back()->getPosition().x, 0);
        sprite_t->setScale(scaleX, scaleY);
        sprites.push_back(sprite_t);
    }
    auto sprite_1 = make_shared<Sprite>();
    sprite_1->setTexture(texture);
    sprite_1->setPosition(-sprite->getGlobalBounds().width, 0);
    sprite_1->setScale(scaleX, scaleY);
    sprites.push_back(sprite_1);
}

void Background::update(float deltaTime, Vector2f position) {
    float movementX = scrollSpeed * deltaTime;
    float movementY = 0;
    float offsetY = position.y - 350;


    //sprite.move(movementX, movementY);
    //sprite2.move(movementX, movementY);

    for (auto& sprite_t : sprites) {
        sprite_t->setPosition(sprite_t->getPosition().x, offsetY);
    }

    //if (sprite.getPosition().x + sprite.getGlobalBounds().width <= position.x - 500) {
    //    sprite.setPosition(sprite2.getPosition().x + sprite2.getGlobalBounds().width, sprite.getPosition().y);
    //}
    //if (sprite2.getPosition().x + sprite2.getGlobalBounds().width <= position.x - 960) {
    //    sprite2.setPosition(sprite.getPosition().x + sprite.getGlobalBounds().width, sprite2.getPosition().y);
    //}
}


void Background::draw(RenderWindow& window) {
    for (auto& sprite_t : sprites) {
        window.draw(*sprite_t);
    }
}