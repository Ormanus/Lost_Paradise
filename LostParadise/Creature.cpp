#include "Creature.h"
#include "Wall.h"

Creature::Creature()
{
}

Creature::~Creature()
{
}

GameObject* Creature::isColliding(int objectType, std::list<GameObject*>* objects)
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
				if (objectType == 1)
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
