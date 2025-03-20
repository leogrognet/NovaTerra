#include "Animation.h"
#include <iostream>

void Animation::animationSwitch(Sprite& sprite,float deltaTime, Vector2f frameSize)
{
	animSwitch += deltaTime;
	if (animSwitch > animTime ) {
		xPos++;
		animSwitch = 0;
	}
	if (xPos > xSizeMax) {
		xPos = 0;
	}
	if (frameSize.x < 0) {
		yPos = 1;
		frameSize.x = frameSize.x * -1;
	}
	else {
		yPos = 0;
	}
	sprite.setTextureRect(IntRect(xPos * frameSize.x, yPos * frameSize.y, frameSize.x, frameSize.y));
}


void Animation::animationChange(Sprite& sprite, Texture& texture) {

	sprite.setTexture(texture);
}

Animation::Animation(Sprite& sprite, Vector2f size, int maxSize, float time)
{
	xPos = 0;
	yPos = 0;
	xSizeMax = maxSize;
	animSwitch = 0;
	animTime = time;
}
