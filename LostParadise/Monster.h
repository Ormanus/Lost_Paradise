#ifndef MONSTER_H
#define MONSTER_H

#include "Creature.h"

class Monster
	:public Creature
{
public:
	Monster();
	~Monster();
	void update(float dt, std::list<GameObject*>* objects)override;
	void draw(sf::RenderWindow* target, sf::RenderStates states = sf::RenderStates::Default) const override;
private:
	void move(std::list<GameObject*>* objects);
};

#endif