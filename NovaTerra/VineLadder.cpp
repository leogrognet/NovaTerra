#include "VineLadder.h"

Vine::Vine(float posX, float posY, float width, float height, bool isStatic, bool asCollision) : Entity(posX, posY, isStatic, asCollision)
{

    m_shapeTexture.loadFromFile("../NovaTerra/assets/Image/Bounce and Move/L.png");
    m_shape.setTexture(m_shapeTexture);
    float scaleFactorX = 32 / m_shape.getGlobalBounds().width;
    float scaleFactorY = 32 / m_shape.getGlobalBounds().height;
    m_shape.setScale({ scaleFactorX,scaleFactorY });
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


