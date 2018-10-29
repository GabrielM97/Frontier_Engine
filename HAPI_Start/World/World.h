#pragma once
#include <HAPI_lib.h>
#include <ctime>
#include <iostream>
#include "../SourceFiles/Vector2D.h"
#include <thread>

class Graphics;
class Entity;


using namespace GM;
using namespace HAPISPACE;
using namespace std;

struct Hit
{
	bool isHit = false;
	std::string direction = " ";

	int calcDirection()
	{
		if (direction == "south" || direction == "east")
			return -1;
		if (direction == "north" || direction == "west")
			return 1;
	}
};

class World
{
public:
	World();
	void Run();
	bool SetupGameWorld();
	void DisplayLogo();
	void createGameWorld();
	Hit checkCollision(std::string n1, int n2);
	void CheckUserInput(std::string name, int controllerId, std::string map = " ");
	virtual ~World();

private:
	const int SCREENWIDTH = 800;
	const int SCREENHEIGHT = 608;
	Graphics *window{nullptr};
	DWORD lastTick = 0;
	unsigned int elaspsTime{ 150 };
	Vector2D velocity;
	Hit hit;
	bool collided = false;


};

