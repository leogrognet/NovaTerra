#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Window/Joystick.hpp>
#include <vector>
#include "RigidBody.h"

using namespace std;
using namespace sf;

class Player {
public:

	RigidBody body;
	enum class State { JUMPING, IDLE, MIDAIR, DASHING };
	enum class Action { DASHING, HOOK, NONE };
	enum class Direction { UP, DOWN, LEFT, RIGHT, UPLEFT, UPRIGHT, DOWNLEFT, DOWNRIGHT };

    Player();

	void update(float deltatime, vector<RectangleShape>& shape);

	void draw(RenderWindow& window);
	void handleInput();

	void dash();
	void grapplinshoot();

    void coutState();

private:
    const float dashspeed = 150.f;

    float speed;
    float jumpspeed;
    float gravity;

    float dtime = 0;
    float time = 0;

    int hp;

	RectangleShape playershape;
	RectangleShape hook;
	float hookSize = 0;

	Clock cd;

	State state;
	Direction direction;
	Action action;

    bool jumpButtonPressed;
    bool canJump;
    bool jumpKeyPressed = false; 
};