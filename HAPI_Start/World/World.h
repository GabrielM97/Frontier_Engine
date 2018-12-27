#pragma once
#include <HAPI_lib.h>
#include <ctime>
#include <iostream>
#include "../Add_On/Vector2D.h"
#include <thread>
#include <vector>
#include <unordered_map>
#include "..\Sound\Sound.h"

class Graphics;
class Entity;
class PlayerEntity;
class EnemyEntity;
class TileMapEntity;
class XMLParser;
class StringHandler;


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


enum class GameState
{
	Menu = 0,
	InGame = 1,
	Paused = 2,
	Ended = 3
};
class World
{
public:
	World();
	void DisplayMenu();
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
	GameState gameState = GameState::Menu;
	Graphics *window{nullptr};
	DWORD lastTick = 0;
	unsigned int simulationTime{ 32 };
	unsigned int menuTime{ 64 };
	Vector2D velocity;
	Hit hit;
	bool collided = false;
	Sound sounds;
	std::vector<PlayerEntity*> playerEntities;
	std::vector<EnemyEntity*>	enemyEntities;
	std::vector<TileMapEntity*> tileentities;
	std::vector<Entity*> entities;

};

