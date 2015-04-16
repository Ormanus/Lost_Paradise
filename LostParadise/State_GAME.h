#ifndef STATE_GAME_H
#define STATE_GAME_H

#include "GameState.h"

//Ors
#include "Level.h"

#include <SFML/Graphics.hpp>


class State_GAME : public GameState
{
public:
	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();

	State_GAME(Game* game);

private:
	sf::View gameView;
	sf::View guiView;

	//Ors
	Level* level;

	void pause();
};
#endif