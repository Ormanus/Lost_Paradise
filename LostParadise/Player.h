#ifndef PLAYER_H
#define PLAYER_H

#include "Creature.h"
#include "CollisionDetector.h"

class Player
	: public Creature
{
public:
	Player();
	~Player();
	void update(float dt) override;
	void draw(sf::RenderWindow* target, sf::RenderStates states = sf::RenderStates::Default) const override;
	void eventUpdate(sf::Event* event);
	void setDetector(CollisionDetector* detector){ this->detector = detector; }
private:
	int ammo;
	CollisionDetector* detector;
};

#endif