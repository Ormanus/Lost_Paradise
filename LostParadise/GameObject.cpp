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
	this->sprite = sprite;
}

void GameObject::setSprite(sf::Texture* texture)
{
	sprite = new sf::Sprite(*texture);
}

void GameObject::update(float dt)
{

}