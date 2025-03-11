#pragma once
#include <SFML/Graphics.hpp>


using namespace sf;
using namespace std;
class RigidBody {
public:
	Vector2f position;
	Vector2f velocity;
	bool isGrounded;

	void groundCollision(vector<RectangleShape>& grounds, const FloatRect& selfShape);

	RigidBody(Vector2f pos);

};