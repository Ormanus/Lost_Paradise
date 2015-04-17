#ifndef GOAL_H
#define GOAL_H

//#include "GameObject.h"
#include "Wall.h"

class Goal
	: public Wall
{
public:
	Goal(){ type = 4; }
	Goal(float w, float h){ type = 4; }
private:
};

#endif