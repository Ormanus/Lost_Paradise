#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

class GameObject
{
public:
	GameObject();
	~GameObject();
	virtual void update() = 0;
	virtual void draw() = 0;
private:

};



#endif