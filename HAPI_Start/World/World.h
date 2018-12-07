#pragma once
#include <HAPI_lib.h>
#include <ctime>
#include <iostream>
#include "../Add_On/Vector2D.h"
#include <thread>
#include <vector>

class Graphics;
class Entity;
class PlayerEntity;
class TileMapEntity;

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
	bool checkCollision(Entity *e);
	
	
	void CheckUserInput(Entity * e, int controllerID);
	virtual ~World();

private:
	const int SCREENWIDTH = 800;
	const int SCREENHEIGHT = 600;
	Graphics *window{nullptr};
	DWORD lastTick = 0;
	unsigned int simulationTime{ 16 };
	Vector2D velocity;
	Hit hit;
	bool collided = false;
	std::vector<PlayerEntity*> playerEntities;
	std::vector<TileMapEntity*> tileentities;
	std::vector<Entity*> entities;

};

