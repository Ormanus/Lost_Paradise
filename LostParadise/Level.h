#ifndef LEVEL_H
#define LEVEL_H

#include <list>
#include "GameObject.h"
#include "Player.h"
#include "Game.h"

class Level
{
public:
	Level(Game* gamePtr);
	~Level();
	void init();
	void update(float deltaTime);
	void draw();
	sf::RenderWindow* getWindow(){ return window; }
private:
	std::list<GameObject*> objects;
	std::list<GameObject*> nonStaticObjects;
	sf::RenderWindow* window;
	sf::View view;
	std::vector<sf::Texture*> textures;
	Player* player;
	int shootingTimer;
	Game* game;
	int levelNumber = 0;
	int levels = 1;

	void loadTextures();
	void loadTexture(std::string path);
	void loadLevel();
	GameObject* addObject(float x, float y, int type);
	void removeObject(GameObject* obj);
	void levelComplete();
};


#endif