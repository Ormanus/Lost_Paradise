#ifndef BULLET_H
#define BULLET_H

#include "GameObject.h"

class Bullet
	:public GameObject
{
public:
	Bullet(float x, float y, float direction = 0);
	~Bullet();
	void update(float dt, std::list<GameObject*>* objects)override;
	void draw(sf::RenderWindow* target, sf::RenderStates states = sf::RenderStates::Default) const override;
	GameObject* detectCollision(std::list<GameObject*>* objects);
private:
	float direction;
};

#endif