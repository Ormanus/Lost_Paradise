#include "Game.h"
#include "GameState.h"

#include <SFML/System.hpp>


Game::Game()
{
	this->window.create(sf::VideoMode(1280, 800), "Manager");
	this->window.setFramerateLimit(60);
}
Game::~Game()
{
	while (!this->states.empty()) popState();
}

//Lisää staten
void Game::pushState(GameState* state)
{
	this->states.push(state);

	return;
}

//Lopettaa staten
void Game::popState()
{
	delete this->states.top();
	this->states.pop();

	return;
}

//Vaihtaa staten
void Game::changeState(GameState* state)
{
	if (!this->states.empty())
	{
		popState();
	}
	pushState(state);

	return;
}

//Tarkistaa staten
GameState* Game::peekState()
{
	if (this->states.empty()) return nullptr;
	return this->states.top();
}

//Peli-ikkuna-looppi-juttu
void Game::gameLoop()
{
	sf::Clock clock;

	while (this->window.isOpen())
	{
		sf::Time elapsed = clock.restart();
		float dt = elapsed.asSeconds();

		if (peekState() == nullptr) continue;
		peekState()->handleInput();
		peekState()->update(dt);
		this->window.clear(sf::Color::White);
		peekState()->draw(dt);
		this->window.display();
	}
}