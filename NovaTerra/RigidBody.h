#pragma once
#include <SFML/Graphics.hpp>


using namespace sf;
using namespace std;
class RigidBody {
public:
	Vector2f position;
	Vector2f velocity;
	Vector2f acceleration;
	float mass;
	float restitution;
	bool isGrounded;
	bool isTouchingWall;
	bool isTouchingCeiling;

	void applyForce(Vector2f force);

	void update(float deltaTime);

	void groundCollision(vector<RectangleShape>& grounds, const FloatRect& selfShape);

	RigidBody(Vector2f pos, float m) : position(pos), velocity(0, 0), acceleration(0, 0), mass(m), isGrounded(false) {}

};