#ifndef WALL_H
#define WALL_H

#include "GameObject.h"

class Wall
	: public GameObject
{
public:
	Wall();
	Wall(float width, float height);
	virtual ~Wall();
	virtual void update(float dt, std::list<GameObject*>* objects) override;
	virtual void draw(sf::RenderWindow* target, sf::RenderStates states) const override;
	virtual void setSprite(sf::Sprite* sprite) override;
	virtual void setSprite(sf::Texture* texture) override;
	virtual void setSolid(bool state){ solid = state; };
	virtual bool isSolid(){ return solid; }
protected:
	bool solid = true;
};

#endif