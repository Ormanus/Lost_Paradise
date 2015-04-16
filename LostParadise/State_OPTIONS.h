#ifndef STATE_OPTIONS_H
#define STATE_OPTIONS_H

#include "GameState.h"

#include <SFML/Graphics.hpp>


class State_OPTIONS : public GameState
{
public:
	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();

	State_OPTIONS(Game* game);

private:
	sf::View view;

	void mainmenu();
};
#endif