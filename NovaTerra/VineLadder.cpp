#include "VineLadder.h"

Vine::Vine(float posX, float posY, float width, float height , bool isStatic, bool asCollision, vector<shared_ptr<Texture>>& texture) : Entity(posX, posY, isStatic, asCollision, texture)
{
    if (!textureList.empty()) {

        m_shape.setTexture(*textureList.at(0).get());
        IntRect m_textureRect(128, 640, 128, 128);

        m_shape.setTextureRect(m_textureRect);
        m_shape.setScale(width, height);
        m_shape.setPosition(posX, posY);
    }
}

void Vine::update(float deltaTime, const vector<shared_ptr<Entity>>& colliders)
{
    for (auto& entity : colliders) {
        if (entity->getID() == 1 && (Keyboard::isKeyPressed(Keyboard::Z) || (Joystick::isConnected(0) && Joystick::getAxisPosition(0, Joystick::Y) < -50))
            && entity->getSprite().getGlobalBounds().intersects(m_shape.getGlobalBounds())) {

            if (auto player = dynamic_cast<Player*>(entity.get())) {
                player->setAction(Player::Action::GRABING);
            }
        }
    }
    Entity::update(deltaTime,colliders);
}

void Vine::draw(RenderWindow& window)
{
    window.draw(m_shape);
}

int Vine::getID()
{
    return 5;
}


