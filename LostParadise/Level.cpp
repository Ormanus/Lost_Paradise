#include "Level.h"
#include "Wall.h"
#include "CollisionDetector.h"

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
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window->close();
		}
		else 
		{
			player->eventUpdate(&event);
		}
	}
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
	window->setVerticalSyncEnabled(true);

	//load textures:
	loadTexture("sprites\\default.png");
	loadTexture("sprites\\player.png");
	loadTexture("sprites\\wall.png");
	loadTexture("sprites\\wall_rusted.png");
	loadTexture("sprites\\wall_reinforced.png");

	//create GameObjects
	player = new Player();
	detector = new CollisionDetector(&objects);
	sf::Sprite* spr = new sf::Sprite(*textures[0]);
	spr->setScale(1, 2);
	player->setSprite( spr );
	player->setDetector(detector);
	objects.push_back(player);

	GameObject* obj = 0;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			obj = new Wall(64, 64);
			obj->setSprite(new sf::Sprite(*textures[(j % 4) + 1]));
			obj->setPosition(i*64, j*64 + 128);
			objects.push_back(obj);
		}
	}
	detector->setVector(&objects);

}

void Level::loadTexture(std::string path)
{
	sf::Texture* texture = new sf::Texture();
	texture->loadFromFile(path);
	textures.push_back(texture);
}