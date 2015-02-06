#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include "GameObject.h"

class Level
{
public:
	Level();
	~Level();
	void init();
	void update(float deltaTime);
	void draw();
private:
	std::vector<GameObject*> objects;
	sf::RenderWindow* window;
};


#endif