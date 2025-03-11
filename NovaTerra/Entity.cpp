#include "Entity.h"

Entity::Entity(Texture& texture, float posX, float posY) {
    sprite.setTexture(texture);
    sprite.setPosition(posX, posY);
}

Sprite& Entity::getSprite()
{
    return sprite;
}


bool Entity::collision(FloatRect& collidedEntity) {
    return collidedEntity.intersects(sprite.getGlobalBounds());
}




