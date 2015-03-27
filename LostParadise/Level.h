#ifndef LEVEL_H
#define LEVEL_H

#include <list>
#include "GameObject.h"
#include "Player.h"

class Level
{
public:
	Level();
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
	void loadTextures();
	void loadTexture(std::string path);
	void loadLevel(int index);
	int shootingTimer;
};


#endif