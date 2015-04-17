#include "GameState.h"
#include "State_GAME.h"
#include "State_MENU.h"
#include "State_OPTIONS.h"
//#include "TextureManager.h"

#include <SFML/Graphics.hpp>

//PÄÄVALIKKO-STATE


State_MENU::State_MENU(Game* game)
{	
	this->game = game;
	sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());

	if (!MenuBG.loadFromFile("Sprites/MainMenu.png"))
	{
		std::cout << "Virhe taustaa ladattaessa!" << std::endl;
	}
}

void State_MENU::draw(const float dt)
{
	this->game->window.setView(this->view);
	this->game->window.clear(sf::Color::Black);

	sf::Sprite sprite;
	sprite.setTexture(MenuBG);
	this->game->window.draw(sprite);
	return;
}

void State_MENU::update(const float dt)
{
}

void State_MENU::handleInput()
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
				if (event.key.code == sf::Keyboard::Escape) this->game->window.close();
				else if (event.key.code == sf::Keyboard::Space) this->loadgame();
				else if (event.key.code == sf::Keyboard::O) this->options();
				break;
			}
			default:
				break;
		}
	}
	return;
}

void State_MENU::loadgame()
{
	this->game->pushState(new State_GAME(this->game));

	return;
}

void State_MENU::options()
{
	this->game->pushState(new State_OPTIONS(this->game));

	return;
}