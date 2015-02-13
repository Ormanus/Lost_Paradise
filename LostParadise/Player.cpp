#include "Player.h"

#define PI 3.14159265358979323846264338327950

Player::Player()
{

	speed = 1;
}

Player::~Player()
{
	delete sprite;
}

void Player::update(float dt)
{
	sf::Vector2f pos = position;
	pos.x += std::cos(direction * PI / 180) * speed;
	pos.y += std::sin(direction * PI / 180) * speed;
	setPosition(pos);
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
