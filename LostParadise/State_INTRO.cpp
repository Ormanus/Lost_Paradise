#include "State_INTRO.h"
#include "State_MENU.h"


State_INTRO::State_INTRO(Game* game)
{
	this->game = game;
	sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());

	if (!picture.loadFromFile("Sprites/Intro.png"))
	{
		std::cout << "Virhe taustaa ladattaessa!" << std::endl;
	}
}

State_INTRO::~State_INTRO()
{
}

void State_INTRO::draw(const float dt)
{
	this->game->window.clear(sf::Color::Black);

	sf::Sprite sprite;
	sprite.setTexture(picture);
	this->game->window.draw(sprite);

	if (timer < 1)
	{
		sf::RectangleShape darkness(sf::Vector2f(game->window.getSize()));
		float alpha = 255 * (1 - timer);
		darkness.setFillColor(sf::Color(0, 0, 0, alpha));
		this->game->window.draw(darkness);

	}

	//if (position.y > 8000) // fade to black when falling too low
	//{
	//	float viewWidth = target->getSize().x, viewHeight = target->getSize().y;
	//	sf::RectangleShape darkness(sf::Vector2f(viewWidth, viewHeight));
	//	darkness.setPosition(target->getView().getCenter().x - viewWidth / 2,
	//		target->getView().getCenter().y - viewHeight / 2);
	//	float alpha = 255 * ((position.y - 8000) / 2000);
	//	darkness.setFillColor(sf::Color(0, 0, 0, alpha));
	//	target->draw(darkness);
	//}

	return;
}

void State_INTRO::update(const float dt)
{
	timer -= dt;
	if (timer < 0)
	{
		this->game->changeState(new State_MENU(game));
	}
}

void State_INTRO::handleInput()
{
	sf::Event event;

	while (active && this->game->window.pollEvent(event))
	{
		switch (event.type)
		{
			//Ikkuna suljetaan
		case sf::Event::Closed:
		{
			game->window.close();
			break;
		}
			//Ikkunan kokoa muutetaan
		case sf::Event::Resized:
		{
			this->view.setSize(event.size.width, event.size.height);
			break;
		}
			//Nappuloita painellaan
		case sf::Event::KeyPressed:
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				this->game->window.close();
			}
			else
			{
				this->game->changeState(new State_MENU(game));
				active = false;
				break;
			}
			break;
		}
		default:
			break;
		}
	}
	return;
}