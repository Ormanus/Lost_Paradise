#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SFML\Graphics.hpp>
#include <list>

class GameObject
{
public:
	GameObject();
	~GameObject();
	virtual void setSprite(sf::Sprite* sprite);
	virtual void setSprite(sf::Texture* texture);
	void setPosition(sf::Vector2f pos){ position = pos; }
	void setPosition(float x, float y){ position.x = x; position.y = y; }
	void setSize(sf::Vector2f size){ this->size = size; }
	void destroy(){ remove = true; }
	bool isDestroyed(){ return remove; }
	sf::Vector2f getPosition(){ return position; }
	sf::Vector2f getSize(){ return size; }
	int getType(){ return type; }
	virtual void update(float dt, std::list<GameObject*>* objects) = 0;
	virtual void draw(sf::RenderWindow* target, sf::RenderStates states = sf::RenderStates::Default) const = 0;
protected:
	sf::Sprite* sprite;
	int type; //TODO: different objects have different types
	sf::Vector2f position;
	sf::Vector2f size;
	bool remove = false;
};



#endif