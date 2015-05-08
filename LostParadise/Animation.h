#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML\Graphics\Sprite.hpp>

class Animation
{
public:
	Animation(sf::Texture* texture, int width);
	~Animation();
	sf::Sprite* getSprite();
	void setImage();
	void setSpeed();
	void update(float dt);
private:
	int spriteWidth,
		//spriteHeight,
		imageNumber,
		imageIndex;
	float timer,
		fullTime;
	sf::Texture* texture;
	sf::Sprite* sprite;
};



#endif