#include "Level.h"
#include "Wall.h"
#include <fstream>
#include "Monster.h"

Level::Level()
{
	init();
}

Level::~Level()
{
	for (int i = 0; i < textures.size(); i++)
	{
		delete textures[i];
		textures[i] = nullptr;
	}

	for (auto it : objects)
	{
		delete it;
		it = nullptr;
	}
	delete window;
}

void Level::update(float deltaTime)
{
	//tämä metodi käskee kaikkia GameObjecteja päivittymään

	//tarkistetaan, onko ikkuna auki:
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window->close();
		}
	}
	
	//Gameobjectit, joilla on update-metodissa jotain toimintaa, päivitetään:

	for (GameObject* it : nonStaticObjects)
	{
		(*it).update(deltaTime, &objects);
	}
}

void Level::draw()
{
	//piirtää kaiken
	window->clear(sf::Color(32, 16, 8));

	sf::Vector2f center = player->getPosition();
	center.x += player->getSize().x/2;
	center.y += player->getSize().y / 2;
	view.setCenter(center);
	window->setView(view);

	for (GameObject* it : objects){
		(*it).draw(window);
	}
	window->display();
}

void Level::init()
{
	//luo ikkunan (kannattaa ehkä siirtää state manageriin?)
	window = new sf::RenderWindow(sf::VideoMode(1280, 800), "Lost Paradise");
	window->setFramerateLimit(60);
	window->setVerticalSyncEnabled(true);

	view = sf::View(sf::FloatRect(0, 0, 1280 / 2, 800 / 2));
	window->setView(view);

	//lataa kentän tekstuurit
	loadTextures();

	//create GameObjects
	player = new Player();
	player->setPosition(128, -64);
	sf::Sprite* spr = new sf::Sprite(*textures[0]);
	spr->setScale(1, 2);
	player->setSprite( spr );
	objects.push_back(player);
	nonStaticObjects.push_back(player);

	Monster* monster = new Monster();
	monster->setPosition(256, -64);
	sf::Sprite* spr2 = new sf::Sprite(*textures[2]);
	spr2->setScale(0.5, 1);
	monster->setSprite(spr2);
	objects.push_back(monster);
	nonStaticObjects.push_back(monster);

	loadLevel(0);

	//detector->setVector(&objects);
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
	//std::ifstream inFile("levels\\level-0.txt", std::ios::binary|std::ios::in);

	//if (inFile)
	//{
	//	//level size = 32*32 tiles
	//	for (int i = 0; i < 16; i++)
	//	{
	//		for (int j = 0; j < 16; j++)
	//		{
	//			char tile;
	//			inFile.read(&tile, sizeof(char));
	//			if (tile != 0){
	//				GameObject* obj = 0;
	//				obj = new Wall(32, 32);
	//				obj->setSprite(new sf::Sprite(*textures[tile]));
	//				obj->setPosition(j*32 + 128, i*32);
	//				objects.push_back(obj);

	//			}
	//		}
	//	}
	//}

	GameObject* obj = new Wall(512, 64);
	obj->setSprite(new sf::Sprite(*textures[2]));
	obj->setPosition(0, 64);
	objects.push_back(obj);

	obj = new Wall(64, 64);
	obj->setSprite(new sf::Sprite(*textures[3]));
	obj->setPosition(512-64, 0);
	objects.push_back(obj);

	obj = new Wall(32, 32);
	obj->setSprite(new sf::Sprite(*textures[4]));
	obj->setPosition(512-96, 32);
	objects.push_back(obj);
}