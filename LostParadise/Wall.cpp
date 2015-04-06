#include "Wall.h"

Wall::Wall()
{
	size.x = 64;
	size.y = 64;
	type = 1;
}

Wall::Wall(float width, float height)
{
	size.x = width;
	size.y = height;
	type = 1;
}

Wall::~Wall()
{
	delete sprite;
}

void Wall::update(float dt, std::list<GameObject*>* objects)
{

}

void Wall::setSprite(sf::Sprite* sprite){
	GameObject::setSprite(sprite);
	//size.x = width;
	//size.y = height;
	//sprite->setScale(size.x / 64, size.y / 64);
}

void Wall::setSprite(sf::Texture* texture){
	GameObject::setSprite(texture);
	sf::Vector2u textureSize = texture->getSize();
	if (textureSize.x > size.x || textureSize.y > size.y)
	{
		float XScale = size.x / textureSize.x,
			YScale = size.y / textureSize.y;

		sprite->setTextureRect(sf::IntRect(0, 0, size.x / XScale, size.y / YScale));
		sprite->setScale(XScale, YScale);
	}
}

void Wall::draw(sf::RenderWindow* target, sf::RenderStates states) const
{
	sprite->setPosition(position);
	target->draw(*sprite);
}