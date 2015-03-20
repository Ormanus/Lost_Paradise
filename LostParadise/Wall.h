#ifndef WALL_H
#define WALL_H

#include "GameObject.h"

class Wall
	: public GameObject
{
public:
	Wall();
	Wall(float width, float height);
	~Wall();
	void update(float dt, std::list<GameObject*>* objects) override;
	void draw(sf::RenderWindow* target, sf::RenderStates states) const override;
	void setSprite(sf::Sprite* sprite) override;
	void setSprite(sf::Texture* texture) override;
private:
	//float width, height;
};

#endif