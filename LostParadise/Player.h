#ifndef PLAYER_H
#define PLAYER_H

#include "Creature.h"
#include "Animation.h"

class Player
	: public Creature
{
public:
	Player();
	~Player();
	void update(float dt, std::list<GameObject*>* objects) override;
	void draw(sf::RenderWindow* target, sf::RenderStates states = sf::RenderStates::Default) const override;
	int getAmmo(){ return ammo; }
	void shoot(){ ammo--; };
private:
	int ammo;
	sf::Texture* armTexture;
	sf::Sprite* armSprite;

	sf::Texture* playerTexture;
	Animation* animation;

	sf::Texture* bulletTexture;
	sf::Sprite* bulletSprite;
};

#endif