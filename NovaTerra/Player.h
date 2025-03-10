#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class Player {
public:
	
	enum class State{ JUMPING, DOUBLEJUMP, DASHING, IDLE, MOVING };

	Player();

	void update(float deltatime);
	void draw(RenderWindow& window);
	void handleInput(float deltatime);
	void jump(float deltatime);
	void dash(float deltatime);

	void coutState();

private:

	float speed;
	float jumpspeed;
	float gravity;

	float time = 0;

	int hp;

	RectangleShape playershape;
	Clock cd;

	char lastKey;

	State state;
};