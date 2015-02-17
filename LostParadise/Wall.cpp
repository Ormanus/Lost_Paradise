#include "Wall.h"

Wall::Wall()
{
	Wall(64, 64);
}

Wall::Wall(float width, float height)
{
	size.x = width;
	size.y = height;
	type = 1;
}

Wall::~Wall()
{
	delete sprite;
}

void Wall::update(float dt)
{

}

void Wall::setSprite(sf::Sprite* sprite){
	GameObject::setSprite(sprite);
	//size.x = width;
	//size.y = height;
	sprite->setScale(size.x / 64, size.y / 64);
}

void Wall::setSprite(sf::Texture* texture){
	GameObject::setSprite(texture);
	sprite->setScale(size.x / 64, size.y / 64);
}

void Wall::draw(sf::RenderWindow* target, sf::RenderStates states) const
{

	sprite->setPosition(position);
	target->draw(*sprite);
}