#include "SFML\Graphics.hpp"
#include "State_MENU.h"
#include "State_INTRO.h"
#include "Game.h"

int main()
{
	Game game;

	game.pushState(new State_INTRO(&game));
	game.gameLoop();

	return 0;
}