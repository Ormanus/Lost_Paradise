#include "Level.h"
#include "Wall.h"
#include "CollisionDetector.h"
#include <fstream>

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
	window->clear(sf::Color(32, 16, 8));
	std::vector<GameObject*>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		(**it).draw(window);
	}
	window->display();
}

void Level::init()
{
	window = new sf::RenderWindow(sf::VideoMode(640, 480), "Lost Paradise");
	window->setFramerateLimit(60);
	window->setVerticalSyncEnabled(true);

	loadTextures();

	//create GameObjects
	player = new Player();
	detector = new CollisionDetector(&objects);
	sf::Sprite* spr = new sf::Sprite(*textures[0]);
	spr->setScale(1, 2);
	player->setSprite( spr );
	player->setDetector(detector);
	objects.push_back(player);

	loadLevel(0);

	detector->setVector(&objects);
}

void Level::loadTexture(std::string path)
{
	sf::Texture* texture = new sf::Texture();
	texture->loadFromFile(path);
	textures.push_back(texture);
}

void Level::loadTextures()
{
	//load textures:

	loadTexture("sprites\\default.png"); //0
	loadTexture("sprites\\player.png");
	loadTexture("sprites\\wall.png");
	loadTexture("sprites\\wall_rusted.png");
	loadTexture("sprites\\wall_reinforced.png"); //4
	loadTexture("sprites\\wall_smooth.png");
	loadTexture("sprites\\wall_smooth_reinforced.png");
	loadTexture("sprites\\green_stuff.png");
	loadTexture("sprites\\wall_rust_bottom.png"); //8
	loadTexture("sprites\\wall_rust_top.png");
	loadTexture("sprites\\wall_rust_bottom_corner.png");
	loadTexture("sprites\\wall_rust_top_corner.png");
	loadTexture("sprites\\bird.png"); //12
	loadTexture("sprites\\tiles.png");
	loadTexture("sprites\\tiles_blue.png");
	loadTexture("sprites\\rainbow.png");
}

void Level::loadLevel(int index)
{
	//open file
	std::ifstream inFile("levels\\level-0.txt", std::ios::binary|std::ios::in);

	if (inFile)
	{
		//level size = 32*32 tiles
		for (int i = 0; i < 16; i++)
		{
			for (int j = 0; j < 16; j++)
			{
				char tile;
				inFile.read(&tile, sizeof(char));
				if (tile != 0){
					GameObject* obj = 0;
					obj = new Wall(16, 16);
					obj->setSprite(new sf::Sprite(*textures[tile]));
					obj->setPosition(j*16 + 128, i*16);
					objects.push_back(obj);

				}
			}
		}
	}
}