#ifndef STATE_END_H
#define STATE_END_H

#include "GameState.h"

#include <SFML/Graphics.hpp>

class State_END
	:public GameState
{
public:
	State_END();
	~State_END();

	State_END(Game* game);

	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();
private:
	bool active = true;

	sf::View view;
	sf::Texture backgroung;

	void mainMenu();
	void playAgain();

};

#endif