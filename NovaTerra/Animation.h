#pragma once
#include <SFML/Graphics.hpp>


using namespace std;
using namespace sf;

class Animation {
private:
	int xPos, yPos, xSizeMax, ySizeMax;
	float animTime, animSwitch;
	bool invert;




public :
	void animationSwitch(Sprite& sprite, float deltaTime, Vector2f frameSize);
	void animationChange(Sprite& sprite, Texture& texture);

	Animation(Sprite& sprite,  Vector2f size, int maxSize, float time);



};