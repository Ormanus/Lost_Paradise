#include "State_END.h"
#include "State_MENU.h"
#include "State_GAME.h"

State_END::State_END()
{
}

State_END::State_END(Game* game)
{
	this->game = game;

	//sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());

	if (!backgroung.loadFromFile("Sprites/Victory.png"))
	{
		std::cout << "Virhe taustaa ladattaessa!" << std::endl;
	}
	this->game->window.setView(game->window.getDefaultView());
}

State_END::~State_END()
{
}

void State_END::draw(const float dt)
{
	this->game->window.clear(sf::Color::Black);

	sf::Sprite sprite;
	sprite.setTexture(backgroung);
	this->game->window.draw(sprite);
}

void State_END::handleInput()
{
	sf::Event event;

	while (active)
	{
		if (this->game->window.pollEvent(event))
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
					this->mainMenu();
					active = false;
				}
				break;
			}
			case sf::Event::MouseButtonPressed:
			{
				sf::Vector2i mousePosition = sf::Mouse::getPosition(this->game->window);

				if (mousePosition.y > 58 && mousePosition.y < 758)
				{
					if (mousePosition.x > 46 && mousePosition.x < 458)
					{
						this->playAgain();
						active = false;
					}
					else if (mousePosition.x > 486 && mousePosition.x < 916)
					{
						this->mainMenu();
						active = false;
					}
				}
				break;
			}
			default:
				break;
			}
		}
	}
	return;
}

void State_END::update(const float dt)
{
	//nothing
}

void State_END::mainMenu()
{
	this->game->changeState(new State_MENU(game));
}

void State_END::playAgain()
{
	this->game->changeState(new State_GAME(game));
}