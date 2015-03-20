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
	float hspeed = 0, vspeed = 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		hspeed++;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		vspeed--;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		hspeed--;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		vspeed++;

	if (hspeed == 0 && vspeed == 0)
	{
		speed = 0;
	}
	else 
	{
		speed = 1;
	}

	//testataan mihin suuntaan pelaaja liikkuu
	direction = atan2f(vspeed, hspeed) * 180 / PI;

	sf::Vector2f pos = position;
	sf::Vector2f prev = position;

	//liikkuminen x-akselilla
	pos.x += std::cos(direction * PI / 180) * speed;
	setPosition(pos);
	if (speed != 0)
	{
		//get collisions
		if (detector != nullptr)
		{
			if (detector->isColliding(this, 1))
			{
				//jos pelaaja törmää, siirretään pelaajaa edelliseen sijaintiin
				setPosition(prev);
			}
		}
	}
	//liikkuminen y-akselilla
	pos = position;
	prev = position;
	pos.y += std::sin(direction * PI / 180) * speed;
	setPosition(pos);
	if (speed != 0)
	{
		//get collisions
		if (detector != nullptr)
		{
			if (detector->isColliding(this, 1))
			{
				//jos pelaaja törmää, siirretään pelaajaa edelliseen sijaintiin
				setPosition(prev);
			}
		}
	}
}

void Player::draw(sf::RenderWindow* target, sf::RenderStates states) const
{
	sprite->setPosition(position);
	target->draw(*sprite);
}
