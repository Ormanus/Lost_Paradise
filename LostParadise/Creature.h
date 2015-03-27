#ifndef CREATURE_H
#define CREATURE_H

#include "SFML\Graphics.hpp"
#include "GameObject.h"

class Creature
	: public GameObject
{
public:
	Creature();
	~Creature();

	//get
	int getHp(){ return hp; }
	int getAttack(){ return attack; }
	int getSpeed(){ return speed; }
	int getDirection(){ return direction; }

	//set
	void setHp(int hp){ this->hp = hp; }
	void setAttack(int attack){ this->attack = attack; }
	void setSpeed(int speed){ this->speed = speed; }
	void setDirection(int direction){ this->direction = direction; }

protected:
	float hp, attack, speed, direction;
	GameObject* isColliding(int objectType, std::list<GameObject*>* objects);
};

#endif