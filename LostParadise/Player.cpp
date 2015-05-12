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

	armTexture = new sf::Texture();
	armTexture->loadFromFile("sprites/Player_hand.png");
	armSprite = new sf::Sprite(*armTexture);
	armSprite->setOrigin(1, 4);

	playerTexture = new sf::Texture();
	playerTexture->loadFromFile("sprites/Player_WALK.png");
	animation = new Animation(playerTexture, 32);

	bulletTexture = new sf::Texture();
	bulletTexture->loadFromFile("sprites/bullet.png");
	bulletSprite = new sf::Sprite(*bulletTexture);
}

Player::~Player()
{
	delete armTexture;
	delete armSprite;
	delete bulletTexture;
	delete bulletSprite;
	delete sprite;
	delete playerTexture;
	delete animation;
}

void Player::update(float dt, std::list<GameObject*>* objects)
{
	animation->update(dt*2);

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
	//draw player body
	//sprite->setPosition(position);
	//target->draw(*sprite);

	//draw animation:
	//switch state

	float rotation = armSprite->getRotation();
	if (rotation > 90 && rotation < 270)
	{
		animation->getSprite()->setScale(-1, 1);
		animation->getSprite()->setPosition(position.x+32, position.y);
	}
	else
	{
		animation->getSprite()->setScale(1, 1);
		animation->getSprite()->setPosition(position);
	}
	target->draw(*(animation->getSprite()));

	//draw arm
	armSprite->setPosition(position.x+16, position.y+24);
	sf::Vector2i mouseWindow = sf::Mouse::getPosition(*target);
	sf::Vector2f mouseWorld = target->mapPixelToCoords(mouseWindow);
	float direction = atan2(mouseWorld.y - position.y - 24, mouseWorld.x - position.x - 16);
	armSprite->setRotation(direction*180/3.14159265358979);
	target->draw(*armSprite);

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

	//draw the amount of bullets
	for (int i = 0; i <= ammo; i++)
	{
		bulletSprite->setPosition(position.x - target->getView().getSize().x / 2 + 16 * i,
			position.y - target->getView().getSize().y / 2 + 32);
		target->draw(*bulletSprite);
	}
}
