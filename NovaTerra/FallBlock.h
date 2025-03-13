#pragma once
#include "Entity.h"


class FallBlock : public Entity {
public:
	FloatRect m_detectionBox;
	FloatRect m_hitBox;
	bool isFalling;
private:
	void update(float deltaTime, FloatRect playerShape);
	void fall(FloatRect playerShape);
	bool crushEntity(FloatRect entity);
};