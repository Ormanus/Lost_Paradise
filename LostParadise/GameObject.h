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
	void setPosition(sf::Vector2f pos){ position = pos; }
	void setPosition(float x, float y){ position.x = x; position.y = y; }
	virtual void update(float dt) = 0;
	virtual void draw(sf::RenderWindow* target, sf::RenderStates states = sf::RenderStates::Default) const = 0;
protected:
	sf::Sprite* sprite;
	int type; //TODO: different objects have different types
	sf::Vector2f position;
};



#endif