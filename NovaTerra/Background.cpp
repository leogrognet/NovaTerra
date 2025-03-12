#include "Background.h"
#include <iostream>

Background::Background(const string& texturePath, float speed) : scrollSpeed(speed) {
    // Charger la texture une seule fois
    if (!texture.loadFromFile("assets/parallaxe/bg.png")) {
        throw runtime_error("Failed to load texture");
    }

    // Initialiser les sprites avec la m�me texture
    sprite.setTexture(texture);
    sprite.setPosition(0, 0);

    sprite2.setTexture(texture);
    sprite2.setPosition(sprite.getGlobalBounds().width, 0);
}

void Background::update(float deltaTime) {
    // D�placer les sprites en fonction de la vitesse de d�filement et du temps �coul�
    sprite.move(scrollSpeed * deltaTime, 0);
    sprite2.move(scrollSpeed * deltaTime, 0);

    // R�initialiser la position des sprites lorsqu'ils sortent de l'�cran
    if (sprite.getPosition().x + sprite.getGlobalBounds().width <= 0) {
        sprite.setPosition(sprite2.getPosition().x + sprite2.getGlobalBounds().width, 0);
    }
    if (sprite2.getPosition().x + sprite2.getGlobalBounds().width <= 0) {
        sprite2.setPosition(sprite.getPosition().x + sprite.getGlobalBounds().width, 0);
    }

    // Messages de d�bogage
    cout << "Sprite 1 position: " << sprite.getPosition().x << ", " << sprite.getPosition().y << endl;
    cout << "Sprite 2 position: " << sprite2.getPosition().x << ", " << sprite2.getPosition().y << endl;
}

void Background::draw(RenderWindow& window) {
    // Dessiner les deux sprites sur la fen�tre
    window.draw(sprite);
    window.draw(sprite2);
}