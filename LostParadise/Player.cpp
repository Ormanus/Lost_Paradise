#include "Player.h"

#define PI 3.14159265358979323846264338327950

Player::Player()
{
	type = 0;
	speed = 1;
	size.x = 32;
	size.y = 64;
}

Player::~Player()
{
	delete sprite;
}

void Player::update(float dt)
{
	sf::Vector2f pos = position;
	sf::Vector2f prev = position;
	pos.x += std::cos(direction * PI / 180) * speed;
	pos.y += std::sin(direction * PI / 180) * speed;
	setPosition(pos);

	if (speed != 0)
	{
		//get collisions
		if (detector != nullptr)
		{
			if (detector->isColliding(this, 1))
			{
				setPosition(prev);
			}
		}
	}
}

void Player::eventUpdate(sf::Event* event)
{
	float xspeed = 0, yspeed = 0;
	if (event->type == sf::Event::KeyPressed)
	{
		
		if (event->key.code == sf::Keyboard::Up)
			direction = -90;
		if (event->key.code == sf::Keyboard::Down)
			direction = 90;
		if (event->key.code == sf::Keyboard::Right)
			direction = 0;
		if (event->key.code == sf::Keyboard::Left)
			direction = 180;
	}
}

void Player::draw(sf::RenderWindow* target, sf::RenderStates states) const
{
	sprite->setPosition(position);
	target->draw(*sprite);
}
