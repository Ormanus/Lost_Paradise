#include "Animation.h"
#include <SFML\Graphics\Texture.hpp>

Animation::Animation(sf::Texture* texture, int width)
{
	this->texture = texture;
	spriteWidth = width;
	imageNumber = texture->getSize().x / width;
	imageIndex = 0;
	fullTime = 0.5;
	timer = fullTime;
	sprite = new sf::Sprite(*texture);
	sprite->setTextureRect(sf::IntRect(imageIndex * spriteWidth, 0, spriteWidth, texture->getSize().y));
}

Animation::~Animation()
{
	delete sprite;
}

sf::Sprite* Animation::getSprite()
{
	return sprite;
}

void Animation::update(float dt)
{
	timer -= dt;
	if (timer < 0)
	{
		timer = fullTime;
		if (++imageIndex == imageNumber)
		{
			imageIndex = 0;
		}
		sprite->setTextureRect(sf::IntRect(imageIndex * spriteWidth, 0, spriteWidth, texture->getSize().y));
	}
}