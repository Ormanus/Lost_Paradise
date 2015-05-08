#include "GameState.h"
#include "State_GAME.h"
#include "State_MENU.h"
#include "State_PAUSE.h"

#include <SFML/Graphics.hpp>

//PAUSSI-STATE


State_PAUSE::State_PAUSE(Game* game)
{
	this->game = game;
	sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());

	if (!PauseBG.loadFromFile("Sprites/Pause.png"))
	{
		std::cout << "Virhe taustaa ladattaessa!" << std::endl;
	}
}

void State_PAUSE::draw(const float dt)
{
	this->game->window.setView(this->game->window.getDefaultView());
	this->game->window.clear(sf::Color::Transparent);
	sf::Sprite sprite;
	sprite.setTexture(PauseBG);
	this->game->window.draw(sprite);

	return;
}

void State_PAUSE::update(const float dt)
{
}

void State_PAUSE::handleInput()
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
				this->mainmenu();
				active = false;
			}
			else if (event.key.code == sf::Keyboard::P)
			{
				this->continuegame();
				active = false;
			}
			break;
		}
		case sf::Event::MouseButtonPressed:
		{
			sf::Vector2i mousePosition = sf::Mouse::getPosition(game->window);
			if (mousePosition.x > 408 && mousePosition.x < 866)
			{
				if (mousePosition.y > 408 && mousePosition.y < 509)
				{
					this->continuegame();
					active = false;
				}
				else if (mousePosition.y > 541 && mousePosition.y < 643)
				{
					this->mainmenu();
					active = false;
				}
			}
			break;
		}
		default:
			break;
		}
	}
	return;
}

void State_PAUSE::mainmenu()
{
	//this->game->pushState(new State_MENU(this->game));
	Game* g = this->game;
	g->popState();
	g->popState();
	return;
}

void State_PAUSE::continuegame()
{
	this->game->popState();//pushState(new State_GAME(this->game));

	return;
}