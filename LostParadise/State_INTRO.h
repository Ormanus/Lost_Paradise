#ifndef STATE_INTRO_H
#define STATE_INTRO_H

#include "GameState.h"

#include <SFML/Graphics.hpp>

class State_INTRO
	:public GameState
{
public:
	State_INTRO();
	~State_INTRO();
	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();

	State_INTRO(Game* game);

private:
	sf::View view;

	sf::Texture picture;

	void loadgame();
	void options();

	float timer = 3;

	bool active = true;
};

#endif