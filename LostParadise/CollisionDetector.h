#ifndef COLLISIONDETECTOR_H
#define COLLISIONDETECTOR_H

#include "GameObject.h"
#include <vector>

class CollisionDetector
{
public:
	CollisionDetector(std::vector<GameObject*>* objects);
	~CollisionDetector();
	void setVector(std::vector<GameObject*>* vector){ objects = vector; }
	bool isColliding(GameObject* obj, int type);
private:
	std::vector<GameObject*>* objects;
};


#endif