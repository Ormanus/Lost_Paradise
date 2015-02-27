#include "CollisionDetector.h"

CollisionDetector::CollisionDetector(std::vector<GameObject*>* objects)
{
}

CollisionDetector::~CollisionDetector()
{
}

bool CollisionDetector::isColliding(GameObject* obj, int type)
{
	//obj on objekti, jolle törmäyksiä testataan
	//type on objektin tyyppi, johon obj voi törmätä

	std::vector<GameObject*>::iterator it;
	it = objects->begin();

	for (; it != objects->end(); it++)
	{
		//varmistetaan, ettei obj törmää itseensä ja että toinen objekti on oikeaa tyyppiä
		if ((*it) != obj && (*it)->getType() == type) 
		{
			if (obj->getPosition().x + obj->getSize().x > (*it)->getPosition().x &&
				obj->getPosition().y + obj->getSize().y > (*it)->getPosition().y &&
				obj->getPosition().x < (*it)->getPosition().x + (*it)->getSize().x &&
				obj->getPosition().y < (*it)->getPosition().y + (*it)->getSize().y
				)
			{
				return true;
			}
		}
	}
	return false;
}
