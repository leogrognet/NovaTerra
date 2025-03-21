 #include "BouncingPlatform.h"

Bounce::Bounce(float posX, float posY, Vector2f size, bool isStatic, bool asCollision) :Entity(posX, posY, isStatic, asCollision)
{
	m_shape.setPosition(posX, posY);
	m_shapeTexture.loadFromFile("../NovaTerra/assets/Image/Bounce and Move/PR.png");

	m_shape.setTexture(m_shapeTexture);

	float scaleFactorX = 128 / m_shape.getGlobalBounds().width / 4;
	float scaleFactorY = 128 / m_shape.getGlobalBounds().height / 4;

	m_shape.setScale({ scaleFactorX,scaleFactorY });
}

void Bounce::update(float deltaTime, const vector<shared_ptr<Entity>>& colliders)
{
	propulse(colliders);
	Entity::update(deltaTime, colliders);
}

void Bounce::draw(RenderWindow& window)
{
	window.draw(m_shape);
}

void Bounce::propulse(const vector<shared_ptr<Entity>>& colliders)
{
	for (auto entity : colliders) {
		if (entity->getID() == 1 && m_shape.getGlobalBounds().intersects(entity->getHitBox().getGlobalBounds())) {
			if (Keyboard::isKeyPressed(Keyboard::Space)) {
				entity->setForcedVelocity({ 0,-150 }); // Attention la vitesse se cumule avec le saut de base mdr
			}	
			else {
				entity->setForcedVelocity({ 0,-200 });
			}
		}
	}
}
