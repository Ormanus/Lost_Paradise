#ifndef PLAYER_H
#define PLAYER_H

#include "Creature.h"

class Player
	: public Creature
{
public:
	Player();
	~Player();
	void update(float dt) override;
	void draw(sf::RenderWindow* target, sf::RenderStates states = sf::RenderStates::Default) const override;
	void eventUpdate(sf::Event* event);
private:
	int ammo;
};

#endif