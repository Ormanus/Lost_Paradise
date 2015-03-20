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
private:

};

#endif