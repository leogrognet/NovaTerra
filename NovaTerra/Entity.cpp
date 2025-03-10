#include "Entity.h"



Entity::Entity(Texture& texture, float posX, float posY) {
    sprite.setTexture(texture);
    sprite.setPosition(posX, posY);
}

Sprite& Entity::getSprite()
{
    return sprite;
}