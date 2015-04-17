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
}

void State_PAUSE::draw(const float dt)
{
	this->game->window.setView(this->pauseView);
	this->game->window.clear(sf::Color::Blue);
	//this->game->window.draw(this->game->background);

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
			this->pauseView.setSize(event.size.width, event.size.height);
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
			else if (event.key.code == sf::Keyboard::Space)
			{
				this->continuegame();
				active = false;
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