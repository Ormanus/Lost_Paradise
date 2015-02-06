#include "SFML\Graphics.hpp"
#include "Level.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 480), "TEST");
	window.setFramerateLimit(60);

	//init level
	Level level;

	sf::Clock Clock;
	while (window.isOpen())
	{

		sf::Time time = Clock.getElapsedTime();
		Clock.restart();
		float dt = time.asMilliseconds() / 1000;

		level.update(dt);

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		window.clear();

		window.display();
	}

	return 0;
}