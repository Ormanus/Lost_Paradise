#include "SFML\Graphics.hpp"
#include "State_MENU.h"
#include "State_INTRO.h"
#include "Game.h"

int main()
{
	Game game;

	game.pushState(new State_INTRO(&game));
	game.gameLoop();


	//initialize level
	//Level level;

	//sf::Clock Clock;
	//sf::RenderWindow* window = level.getWindow();
	//while (window->isOpen()) //game loop
	//{
	//	//siirr� n�m� state manageriin:

	//	sf::Time time = Clock.getElapsedTime();
	//	Clock.restart();
	//	float dt = time.asMilliseconds()/10;
	//	level.update(dt);
	//	level.draw();
	//}

	return 0;
}