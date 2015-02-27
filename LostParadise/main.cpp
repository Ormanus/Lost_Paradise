#include "SFML\Graphics.hpp"
#include "Level.h"

int main()
{
	//initialize level
	Level level;

	sf::Clock Clock;
	sf::RenderWindow* window = level.getWindow();
	while (window->isOpen()) //game loop
	{
		//siirr� n�m� state manageriin:

		sf::Time time = Clock.getElapsedTime();
		Clock.restart();
		float dt = time.asMilliseconds()/10;
		level.update(dt);
		level.draw();
	}

	return 0;
}