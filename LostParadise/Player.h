#ifndef PLAYER_H
#define PLAYER_H

#include "Creature.h"

class Player
	: public Creature
{
public:
	Player();
	~Player();
	void update(float dt, std::list<GameObject*>* objects) override;
	void draw(sf::RenderWindow* target, sf::RenderStates states = sf::RenderStates::Default) const override;
private:
	int ammo;
	bool isColliding(int objectType, std::list<GameObject*>* objects);
};

#endif