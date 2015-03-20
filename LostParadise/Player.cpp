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

void Player::update(float dt, std::list<GameObject*>* objects)
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
		if (isColliding(1, objects))
		{
			//jos pelaaja törmää, siirretään pelaajaa edelliseen sijaintiin
			setPosition(prev);
		}
	}
	//liikkuminen y-akselilla
	pos = position;
	prev = position;
	pos.y += std::sin(direction * PI / 180) * speed;
	setPosition(pos);
	if (speed != 0)
	{
		if (isColliding(1, objects))
		{
			setPosition(prev);
		}
	}
}

void Player::draw(sf::RenderWindow* target, sf::RenderStates states) const
{
	sprite->setPosition(position);
	target->draw(*sprite);
}

bool Player::isColliding(int objectType, std::list<GameObject*>* objects)
{
	for (GameObject* it : *objects)
	{
		if (it != this && it->getType() == objectType)
		{
			if (position.x + size.x > it->getPosition().x &&
				position.y + size.y > it->getPosition().y &&
				position.x < it->getPosition().x + it->getSize().x &&
				position.y < it->getPosition().y + it->getSize().y
				)
			{
				return true;
			}
		}
	}
	return false;
}
