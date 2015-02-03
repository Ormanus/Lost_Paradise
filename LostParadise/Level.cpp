#include "Level.h"

Level::Level()
{
}

Level::~Level()
{
}

void Level::update()
{
	std::vector<GameObject*>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		(**it).update();
	}
}

void Level::draw()
{
	std::vector<GameObject*>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		(**it).draw();
	}
}