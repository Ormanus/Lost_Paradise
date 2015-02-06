#include "Level.h"

Level::Level()
{
	init();
}

Level::~Level()
{
}

void Level::update(float deltaTime)
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
		(**it).draw(window);
	}
}

void Level::init()
{
	//create GameObjects
	for (int i = 0; i < 10; i++)
	{
		//objects.push_back(new Wall(i, 0));
	}
}