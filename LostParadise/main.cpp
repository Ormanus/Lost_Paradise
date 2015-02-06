#include "SFML\Graphics.hpp"
#include "Level.h"

int main()
{
	//init level
	Level level;

	sf::Clock Clock;
	sf::RenderWindow* window = level.getWindow();
	while (window->isOpen())
	{

		sf::Time time = Clock.getElapsedTime();
		Clock.restart();
		float dt = time.asMilliseconds() / 1000;

		level.update(dt);

		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window->close();
			}
		}

		level.draw();
	}

	return 0;
}