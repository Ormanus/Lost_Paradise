#include "Level.h"
#include "Wall.h"

Level::Level()
{
	init();
}

Level::~Level()
{
	for (int i = 0; i < textures.size(); i++)
	{
		delete textures[i];
	}
	delete window;
}

void Level::update(float deltaTime)
{
	std::vector<GameObject*>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		(**it).update(deltaTime);
	}
}

void Level::draw()
{
	window->clear();
	std::vector<GameObject*>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		(**it).draw(window);
	}
	window->display();
}

void Level::init()
{
	window = new sf::RenderWindow(sf::VideoMode(640, 480), "TEST");
	window->setFramerateLimit(60);

	//TODO: recource handler
	sf::Texture* texture = new sf::Texture();
	texture->loadFromFile("sprites\\default.png");
	textures.push_back(texture);
	sf::Sprite* sprite = new sf::Sprite(*textures[textures.size() - 1]);

	//create GameObjects
	for (int i = 0; i < 10; i++)
	{
		GameObject* go;
		go = new Wall();
		go->setSprite(sprite);
		go->setPosition(i*32, 64);
		objects.push_back(go);
	}
}