#include "GameObject.h"

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

void GameObject::draw(sf::RenderWindow* target, sf::RenderStates states) const
{
	
}

void GameObject::setSprite(sf::Sprite* sprite)
{
	sprite->setPosition(position);
	this->sprite = sprite;
}

void GameObject::setSprite(sf::Texture* texture)
{
	sprite = new sf::Sprite(*texture);
	sprite->setPosition(position);
}

void GameObject::update(float dt, std::list<GameObject*>* objects)
{

}
