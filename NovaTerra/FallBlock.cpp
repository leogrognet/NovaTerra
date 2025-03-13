#include "FallBlock.h"

void FallBlock::update(float deltaTime, FloatRect playerShape)
{
	crushEntity(playerShape);
	fall(playerShape);
}

void FallBlock::fall(FloatRect playerShape)
{
	if (playerShape.intersects(m_detectionBox)){
		m_rigidBody.setIsStatic(false);
	}
	else {
		m_rigidBody.setIsStatic(true);
	}
}

bool FallBlock::crushEntity(FloatRect entity) {
	if (entity.intersects(m_hitBox)) {
		return true;
	}
	return false;
}


