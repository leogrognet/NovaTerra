#pragma once
#include <SFML/Graphics.hpp>


using namespace std;
using namespace sf;

class Animation {
private:
	int xPos, yPos, frameSize, xSizeMax, ySizeMax;
	float animTime, animSwitch;


	void animationSwitch(Sprite& sprite,float deltaTime);

	void animationChange(Sprite& sprite, Texture& texture);
public :
	Animation(Sprite& sprite, Texture& texture);

};