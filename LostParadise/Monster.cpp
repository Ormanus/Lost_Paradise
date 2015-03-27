#include "Monster.h"
#include "player.h"

Monster::Monster()
{
	size.x = 32;
	size.y = 64;
	type = 2;
}

Monster::~Monster()
{
}

void Monster::update(float dt, std::list<GameObject*>* objects)
{
	float hspeed = 0, vspeed = 0;
	sf::Vector2f pos = position;
	sf::Vector2f prev = position;
	move(objects);
}


void Monster::move(std::list<GameObject*>* objects)
{
	float hspeed = 0, vspeed = 0;
	sf::Vector2f pos = position;
	sf::Vector2f prev = position;

	bool onGround = true;
	position.y++;
	onGround = (isColliding(1, objects) != nullptr);
	position.y--;


	Player* player = nullptr;
	//find player
	for (auto it : *objects)
	{
		if (it->getType() == 0)
		{
			player = (Player*)it;
		}
	}

	if (player->getPosition().x > position.x)
	{
		hspeed = 2;
	}
	else
	{
		hspeed = -2;
	}
	if (player->getPosition().y < position.y && onGround)
	{
		float dx = player->getPosition().x - position.x,
			dy = player->getPosition().y - position.y;
		if (sqrt(dx*dx+ dy*dy) < 100)
		{
			vspeed -= 10;
		}
	}
	
	vspeed += std::sin(direction) * speed;

	if (hspeed == 0 && vspeed == 0)
	{
		speed = 0;
	}
	else
	{
		speed = sqrt(vspeed*vspeed + hspeed*hspeed);
	}
	//liikkuminen x-akselilla
	pos.x += hspeed;
	setPosition(pos);
	GameObject* other = isColliding(1, objects);
	if (other != nullptr)
	{
		if (pos.x > other->getPosition().x)
		{
			setPosition(other->getPosition().x + other->getSize().x, pos.y);
		}
		else
		{
			setPosition(other->getPosition().x - getSize().x, pos.y);
		}
		hspeed = 0;
		if (player->getPosition().y < position.y)
		{
			//try to jump
			if (onGround)
			{
				vspeed -= 10;
				direction = atan2f(vspeed, hspeed);
				speed = sqrt(vspeed*vspeed + hspeed*hspeed);
			}
		}
	}

	//liikkuminen y-akselilla
	pos = position;
	prev = position;
	pos.y += std::sin(direction) * speed;
	setPosition(pos);
	other = isColliding(1, objects);
	if (other != nullptr)
	{
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
		//prev = position;
		////setPosition(pos);
		//if (isColliding(1, objects) != nullptr)
		//{
		//	setPosition(prev);
		//}
		//else
		if (!onGround)
		{
			vspeed += 0.5;
			if (vspeed > 100)
				vspeed = 100;
		}

		direction = atan2f(vspeed, hspeed);
		speed = sqrt(vspeed*vspeed + hspeed*hspeed);
	}
}

void Monster::draw(sf::RenderWindow* target, sf::RenderStates states) const
{
	sprite->setPosition(position);
	target->draw(*sprite);
}