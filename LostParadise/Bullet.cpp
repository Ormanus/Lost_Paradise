#include "Bullet.h"
#include "Monster.h"
#include "Wall.h"

Bullet::Bullet(float x, float y, float direction)
{
	position.x = x;
	position.y = y;
	this->direction = direction;
	type = 3;
}

Bullet::~Bullet()
{
}

void Bullet::draw(sf::RenderWindow* target, sf::RenderStates states) const
{
	sf::RectangleShape rect(sf::Vector2f(6, 2));
	rect.setOrigin(3, 1);
	rect.setPosition(position);
	rect.setRotation(direction*180/3.14159265);
	target->draw(rect);
}

void Bullet::update(float dt, std::list<GameObject*>* objects)
{
	position.x += cos(direction) * 32;
	position.y += sin(direction) * 32;

	GameObject* other = detectCollision(objects);
	if (other != nullptr)
	{
		if (other->getType() == 2)
		{
			Monster* m = (Monster*)other;
			m->setHp(-1);
		}
		if (other->getType() != 0) //player cannot shoot himself
		{
			destroy();
		}
	}
	timer -= dt;
	if (timer < 0)
	{
		destroy();
	}
}

GameObject* Bullet::detectCollision(std::list<GameObject*>* objects)
{
	for (GameObject* it : *objects)
	{
		if (it != this && it->getType())
		{
			if (position.x + size.x > it->getPosition().x &&
				position.y + size.y > it->getPosition().y &&
				position.x < it->getPosition().x + it->getSize().x &&
				position.y < it->getPosition().y + it->getSize().y
				)
			{
				if (it->getType() == 1)
				{
					if (((Wall*)it)->isSolid())
					{
						return it;
					}
				}
				else
				{
					return it;
				}
			}
		}
	}
	return nullptr;
}