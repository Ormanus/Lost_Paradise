#include "Wall.h"

Wall::Wall()
{
	Wall(64, 64);
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
	sprite->setScale(size.x / 64, size.y / 64);
}

void Wall::setSprite(sf::Texture* texture){
	GameObject::setSprite(texture);
	sprite->setScale(size.x / 64, size.y / 64);
}

void Wall::draw(sf::RenderWindow* target, sf::RenderStates states) const
{
	//sf::Vector2f textureSize = (sf::Vector2f)sprite->getTexture()->getSize();
	//for (unsigned i = 0; i < size.x / textureSize.x; i++)
	//{
	//	for (unsigned j = 0; j < size.y / textureSize.y; j++)
	//	{
	//		sf::Vector2f drawingPosition = position + sf::Vector2f(textureSize.x*i, textureSize.y*j);
	//		sprite->setPosition(drawingPosition);
	//		target->draw(*sprite);
	//	}
	//}
	sprite->setPosition(position);
	target->draw(*sprite);
}