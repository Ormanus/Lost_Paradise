#include "Wall.h"

Wall::Wall()
{
	type = 1;
}

Wall::~Wall()
{
	delete sprite;
}

void Wall::update(float dt)
{

}

void Wall::draw(sf::RenderWindow* target, sf::RenderStates states) const
{
	sprite->setPosition(position);
	target->draw(*sprite);
}