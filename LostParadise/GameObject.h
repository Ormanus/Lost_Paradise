#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SFML\Graphics.hpp>

class GameObject
{
public:
	GameObject();
	~GameObject();
	void setSprite(sf::Sprite* sprite);
	void setSprite(sf::Texture* texture);
	virtual void update() = 0;
	virtual void draw(sf::RenderWindow* target, sf::RenderStates states = sf::RenderStates::Default) const = 0;
private:
	sf::Sprite* sprite;
};



#endif