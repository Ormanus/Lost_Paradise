#include "SFML\Graphics.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 480), "TEST");
	sf::CircleShape shape(50.f);
	shape.setFillColor(sf::Color::Green);
	shape.setPosition(0, 0);
	bool b = 0;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		b = !b;
		shape.setPosition(0.f, (b ? 10.f : 0.f));
		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}