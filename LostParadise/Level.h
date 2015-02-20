#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
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
	std::vector<GameObject*> objects;
	sf::RenderWindow* window;
	std::vector<sf::Texture*> textures;
	Player* player;
	CollisionDetector* detector;
	void loadTextures();
	void loadTexture(std::string path);
	void loadLevel(int index);
	
};


#endif