#ifndef WALL_H
#define WALL_H

#include "GameObject.h"

class Wall
	: public GameObject
{
public:
	Wall();
	~Wall();
	void update(float dt) override;
	void draw(sf::RenderWindow* target, sf::RenderStates states) const override;
private:
};



#endif