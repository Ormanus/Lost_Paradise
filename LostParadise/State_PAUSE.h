#ifndef STATE_PAUSE_H
#define STATE_PAUSE_H

#include "GameState.h"

#include <SFML/Graphics.hpp>


class State_PAUSE : public GameState
{
public:
	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();

	State_PAUSE(Game* game);

private:
	sf::View pauseView;
	bool active = true;

	void mainmenu();
	void continuegame();
};
#endif