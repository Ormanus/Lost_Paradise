#include "GameState.h"
#include "State_GAME.h"
#include "State_MENU.h"
#include "State_PAUSE.h"

#include <SFML/Graphics.hpp>

//PELI-STATE


void State_GAME::draw(const float dt)
{
	this->game->window.clear(sf::Color::White);

	level->draw();

	return;
}

void State_GAME::update(const float dt)
{
	level->update(dt);
	return;
}

void State_GAME::handleInput()
{
	sf::Event event;

	while (this->game->window.pollEvent(event))
	{
		switch (event.type)
		{
		//Ikkuna suljetaan
		case sf::Event::Closed:
			{
				this->game->window.close();
				break;
			}
		//Ikkunan kokoa muutetaan
		case sf::Event::Resized:
			{
				gameView.setSize(event.size.width, event.size.height);
				guiView.setSize(event.size.width, event.size.height);
				break;
			}
		//Nappuloita painelllaan
		case sf::Event::KeyPressed:
		{
			if (event.key.code == sf::Keyboard::P) this->pause();
			break;
		}

		default:
			break;
		}
	}
	return;
}

State_GAME::State_GAME(Game* game)
{
	this->game = game;
	sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
	this->guiView.setSize(pos);
	this->gameView.setSize(pos);
	pos *= 0.5f;
	this->guiView.setCenter(pos);
	this->gameView.setCenter(pos);

	//TODO: lisää destruktoriin
	level = new Level(game);
}

void State_GAME::pause()
{
	this->game->pushState(new State_PAUSE(this->game));

	return;
}