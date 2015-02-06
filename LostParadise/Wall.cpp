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
	position.x++;
	if (position.x > 480)
	{
		position.x = 0;
	}
}

void Wall::draw(sf::RenderWindow* target, sf::RenderStates states) const
{
	target->draw(*sprite);
}