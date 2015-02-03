#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include "GameObject.h"

class Level
{
public:
	Level();
	~Level();
	void update();
	void draw();
private:
	std::vector<GameObject*> objects;
};


#endif