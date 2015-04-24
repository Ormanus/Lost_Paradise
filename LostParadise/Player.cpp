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
	hp = 10;
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
		hspeed+=5;
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
		hspeed-=5;

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
		prev = position;
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
	}
	if (isColliding(4, objects))
	{
		destroy();
	}

	if (position.y > 10000)
	{
		setHp(-1);
	}
}

void Player::draw(sf::RenderWindow* target, sf::RenderStates states) const
{
	sprite->setPosition(position);
	target->draw(*sprite);

	if (hp < 10)//hp bar
	{
		sf::RectangleShape bar(sf::Vector2f(10 * hp, 8));
		bar.setFillColor(sf::Color::Green);
		bar.setPosition(position.x - 50 + 16, position.y - 16);
		target->draw(bar);
	}

	if (position.y > 8000) // fade to black when falling too low
	{
		float viewWidth = target->getSize().x, viewHeight = target->getSize().y;
		sf::RectangleShape darkness(sf::Vector2f(viewWidth, viewHeight));
		darkness.setPosition(target->getView().getCenter().x - viewWidth/2, 
			target->getView().getCenter().y - viewHeight / 2);
		float alpha = 255 * ((position.y - 8000) / 2000);
		darkness.setFillColor(sf::Color(0, 0, 0, alpha));
		target->draw(darkness);
	}
}
