#include "FallBlock.h"

void FallBlock::update(float deltaTime, FloatRect playerShape, std::vector<RectangleShape> colliders)
{

	m_body.groundCollision(colliders, m_colliderBox);
	fall(playerShape);
	m_body.update(deltaTime);
}

void FallBlock::fall(FloatRect playerShape)
{
	if (playerShape.intersects(m_detectionBox)){
		m_body.setIsGrounded(false);
	}
	else {
		m_body.setIsGrounded(true);
	}
}


