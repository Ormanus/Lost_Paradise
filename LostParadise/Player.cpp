#include "Player.h"
#include <iostream>

#define PI 3.14159265358979323846264338327950

Player::Player()
{
	type = 0;
	speed = 1;
	size.x = 32;
	size.y = 64;
	ammo = 6;
}

Player::~Player()
{
	delete sprite;
}

void Player::update(float dt, std::list<GameObject*>* objects)
{
	float hspeed = 0, vspeed = 0;
	sf::Vector2f pos = position;
	sf::Vector2f prev = position;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		hspeed+=3;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		position.y++;
		if (isColliding(1, objects) != nullptr)
		{
			vspeed = -10;
		}
		position = prev;
		//pos = position;
		//vspeed -= 5;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		hspeed-=3;

	vspeed += std::sin(direction) * speed;
	
	if (hspeed == 0 && vspeed == 0)
	{
		speed = 0;
	}
	else 
	{
		speed = sqrt(vspeed*vspeed + hspeed*hspeed);
	}

	direction = atan2f(vspeed, hspeed);
	//liikkuminen x-akselilla
	pos.x += hspeed;
	setPosition(pos);
	GameObject* other = isColliding(1, objects);
	if (other != nullptr)
	{
		//std::cout << "x-collision";
		//jos pelaaja törmää, siirretään pelaajaa seinän viereen
		if (pos.x > other->getPosition().x)
		{
			setPosition(other->getPosition().x + other->getSize().x, pos.y);
		}
		else
		{
			setPosition(other->getPosition().x - getSize().x, pos.y);
		}
		hspeed = 0;
	}
	//liikkuminen y-akselilla
	pos = position;
	prev = position;
	pos.y += std::sin(direction) * speed;
	setPosition(pos);
	other = isColliding(1, objects);
	if (other != nullptr )
	{
		//std::cout << "y-collision\n";
		//setPosition(prev);
		if (pos.y > other->getPosition().y)
		{
			setPosition(pos.x, other->getPosition().y + other->getSize().y);
		}
		else
		{
			setPosition(pos.x, other->getPosition().y - getSize().y);
		}
		vspeed = 0;
		direction = atan2f(vspeed, hspeed);
	}
	else
	{
		//std::cout << "gravity\n";
		prev = position;
		//setPosition(pos);
		if (isColliding(1, objects) != nullptr)
		{
			setPosition(prev);
		}
		else
		{
			vspeed += 0.5;
			if (vspeed > 100)
				vspeed = 100;
		}
			
		direction = atan2f(vspeed, hspeed);
		speed = sqrt(vspeed*vspeed + hspeed*hspeed);
		//std::cout << speed << "\n";
	}
}

void Player::draw(sf::RenderWindow* target, sf::RenderStates states) const
{
	sprite->setPosition(position);
	target->draw(*sprite);
}
