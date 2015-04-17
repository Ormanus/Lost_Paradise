#include "GameState.h"
#include "State_MENU.h"
#include "State_OPTIONS.h"

#include <SFML/Graphics.hpp>

//ASETUKSET-STATE


State_OPTIONS::State_OPTIONS(Game* game)
{
	this->game = game;
	sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
}

void State_OPTIONS::draw(const float dt)
{
	this->game->window.setView(this->view);
	this->game->window.clear(sf::Color::Yellow);
	//this->game->window.draw(this->game->background);

	return;
}

void State_OPTIONS::update(const float dt)
{
}

void State_OPTIONS::handleInput()
{
	sf::Event event;

	while (this->game->window.pollEvent(event))
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
			if (event.key.code == sf::Keyboard::Escape) this->mainmenu();
			break;
		}
		default:
			break;
		}
	}
	return;
}

void State_OPTIONS::mainmenu()
{
	this->game->pushState(new State_MENU(this->game));

	return;
}


