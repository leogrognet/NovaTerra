#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Entity.h"
#include "Cycle.h"
#include "Player.h"

class Firecamp : public Entity {
public:
    sf::CircleShape detectionRange;
    sf::Texture firecampTexture;
    sf::Clock CD;

    Firecamp(float posX, float posY, bool isStatic, bool asCollision);

    void update(float deltaTime, const vector<shared_ptr<Entity>>& colliders)override;
    void draw(RenderWindow& window) override;
    //void interact(Cycle& cycle, Player& player) override;
};