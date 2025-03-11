#include "Animation.h"

void Animation::animationSwitch(Sprite& sprite,float deltaTime)
{
	animSwitch += deltaTime;
	if (animSwitch > animTime) {
		xPos++;
		animSwitch = 0;
	}
	if (xPos > xSizeMax) {
		xPos = 0;
	}

	sprite.setTextureRect(IntRect(xPos * frameSize, yPos * frameSize, frameSize, frameSize));
}

void Animation::animationChange(Sprite& sprite, Texture& texture) {
	sprite.setTexture(texture);
	xSizeMax = sprite.getTextureRect().width;
	ySizeMax = sprite.getTextureRect().height;
}

Animation::Animation(Sprite& sprite, Texture& texture)
{
	xPos = 0;
	yPos = 0;
	animationChange(sprite, texture);
}
