#ifndef STATE_MENU_H
#define STATE_MENU_H

#include "GameState.h"

#include <SFML/Graphics.hpp>


class State_MENU : public GameState
{
public:
	State_MENU();
	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();

	State_MENU(Game* game);

private:
	sf::View view;

	sf::Texture MenuBG;

	void loadgame();
	void options();
};
#endif