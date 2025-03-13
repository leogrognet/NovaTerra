#pragma once
#include "RigidBody.h"


class FallBlock {
public:
	RigidBody m_body;
	FloatRect m_detectionBox;
	FloatRect m_colliderBox;
	bool isFalling;
private:
	void update(float deltaTime, FloatRect playerShape, std::vector<RectangleShape> colliders);
	void fall(FloatRect playerShape);
};