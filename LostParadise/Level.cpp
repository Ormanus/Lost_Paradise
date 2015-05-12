#include "Level.h"
#include "Wall.h"
#include "Goal.h"
#include <fstream>
#include "Monster.h"
#include "Bullet.h"
#include <iostream>
#include <algorithm>
#include "State_GAME.h"
#include "State_END.h"

enum ObjectTypes
{
	TPlayer,
	TWall,
	TMutant,
	TItem,
	TGoal
};

Level::Level(Game* gamePtr)
{
	game = gamePtr;
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
	
	std::list<GameObject*> removeList;

	//Gameobjectit, joilla on update-metodissa jotain toimintaa, päivitetään:
	for (GameObject* it : nonStaticObjects)
	{
		(*it).update(deltaTime, &objects);
		if (it->isDestroyed())
		{
			removeList.push_back(it);
		}
	}

	//ampuminen on levelin updatessa pelaajan sijasta, koska paljon helpompaa...
	if (shootingTimer < 0 && player->getAmmo() > 0)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			sf::Vector2i mouseWindow = sf::Mouse::getPosition(*window);
			sf::Vector2f mouseWorld = window->mapPixelToCoords(mouseWindow);
			float mouseX = mouseWorld.x,
				mouseY = mouseWorld.y;
			float direction = atan2(mouseY - player->getPosition().y - 32, mouseX - player->getPosition().x - 16);
			Bullet* b = new Bullet(player->getPosition().x + 16, player->getPosition().y + 32, direction);
			objects.push_back(b);
			nonStaticObjects.push_back(b);
			shootingTimer = 30;
			player->shoot();
			std::cout << "Mouse: " << mouseX - 640 << ", " << mouseY - 400 << "\n";
		}
	}
	else
	{
		shootingTimer--;
	}

	//poistettavat objektit poistetaan
	for (auto it : removeList)
	{
		if (it == player)
		{
			if (player->getHp() >= 0) //jos pelaaaja ei 'kuollut'
			{
				removeObject(it);
				player = nullptr;
				levelComplete(); //seuraava kenttä
				std::cout << "next\n";
			}
			else
			{
				//aloita alusta
				this->game->changeState(new State_GAME(this->game));
			}
			break;
		}
		else
		{
			removeObject(it);
		}
	}
}

void Level::draw()
{
	//piirtää kaiken
	if (player != nullptr)
	{
		window->clear(sf::Color(32, 16, 8));

		window->setView(window->getDefaultView());

		sf::Sprite bg(*textures[16]);
		bg.setScale(2, 2);
		window->draw(bg);

		sf::Vector2f center = player->getPosition();
		center.x += player->getSize().x / 2;
		center.y += player->getSize().y / 2;
		view.setCenter(center);
		window->setView(view);

		for (GameObject* it : objects){
			(*it).draw(window);
		}
	}
}

void Level::init()
{
	view = sf::View(sf::FloatRect(0, 0, 1280 / 2, 800 / 2));

	window = &(game->window);

	//lataa kentän tekstuurit
	loadTextures();

	loadLevel();

	if (player != nullptr)
	{
		sf::Sprite* spr = new sf::Sprite(*textures[0]);
		spr->setScale(1, 2);
		player->setSprite(spr);
		shootingTimer = 60;
	}
	else
	{
		exit(1);
	}
}

void Level::loadTexture(std::string path)
{
	sf::Texture* texture = new sf::Texture();
	texture->loadFromFile(path);
	texture->setRepeated(true);
	textures.push_back(texture);
	if (texture == nullptr)
	{
		std::cout << "Tekstuurin lataaminen epäonnistui\n";
	}
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
	loadTexture("sprites\\grey_noise.png"); //8
	loadTexture("sprites\\cobble.png");
	loadTexture("sprites\\wall_bg.png");
	loadTexture("sprites\\tiles_brown.png");
	loadTexture("sprites\\bird.png"); //12
	loadTexture("sprites\\tiles.png");
	loadTexture("sprites\\tiles_blue.png");
	loadTexture("sprites\\rainbow.png");
	loadTexture("sprites\\BG.png"); //16
}

GameObject* Level::addObject(float x, float y, int type)
{
	GameObject* obj = nullptr;
	switch (type)
	{
	case TPlayer: 
		if (player == nullptr)
		{
			obj = new Player();
			nonStaticObjects.push_back(obj);
		}
		else
		{
			//player->setPosition(x, y);
		}
		break;
	case TWall:
		obj = new Wall();
		break;
	case TMutant:
		obj = new Monster();
		obj->setSprite(textures[1]);
		nonStaticObjects.push_back(obj);
		break;
	case TGoal:
		obj = new Goal();
		break;
	}

	if (obj != nullptr)
	{
		obj->setPosition(x, y);
		objects.push_back(obj);
	}
	return obj;
}

void Level::removeObject(GameObject* obj)
{
	std::list<GameObject*>::const_iterator it;

	it = std::find(objects.begin(), objects.end(), obj);
	if (it != objects.end())
	{
		std::cout << "erased from objects\n";
		objects.erase(it);
	}

	it = std::find(nonStaticObjects.begin(), nonStaticObjects.end(), obj);
	if (it != nonStaticObjects.end())
	{
		std::cout << "erased from nonStatics\n";
		nonStaticObjects.erase(it);
	}

	std::cout << "deleting object...\n";
	delete obj;
}

void Level::loadLevel()
{
	//for (auto it : objects)
	//{
	//	if (it != player)
	//		removeObject(it);
	//}
	//for (auto it : nonStaticObjects)
	//{
	//	if (it != player)
	//		removeObject(it);
	//}
	objects.clear();
	nonStaticObjects.clear();

	std::ifstream inFile("levels\\level-"+std::to_string(levelNumber)+".txt", std::ios::binary | std::ios::in);
	if (inFile)
	{
		while (!inFile.eof())
		{
			int x, y, w, h, type, subtype;
			GameObject* obj = nullptr;

			inFile.read((char*)&type, sizeof(int));
			inFile.read((char*)&x, sizeof(int));
			inFile.read((char*)&y, sizeof(int));

			obj = addObject(x, y, type);

			switch (type)
			{
			case TPlayer:
				if (player == nullptr)
				player = (Player*)obj;
				break;
			case TWall:
				inFile.read((char*)&w, sizeof(int));
				inFile.read((char*)&h, sizeof(int));
				obj->setSize(sf::Vector2f(w, h));
				inFile.read((char*)&subtype, sizeof(int));
				if (subtype > 127)
				{
					subtype = 255 - subtype;
					((Wall*)obj)->setSolid(false);
				}
				obj->setSprite(textures[subtype]);
				if (subtype == 12)
				{
					objects.pop_back(); //delete wall. TODO: add goal in level editor
					obj = addObject(x, y, 4);
					obj->setSize(sf::Vector2f(w, h));
					obj->setSprite(textures[12]);
				}
				break;
			case TMutant:
				break;
			case TItem:
				break;
			case TGoal:
				break;
			default:
				//FAIL!
				break;
			}
		}
	}
}

void Level::levelComplete()
{
	levelNumber++;
	if (levelNumber == levels)
	{
		this->game->changeState(new State_END(game));
	}
	else
	{
		loadLevel();
	}
}