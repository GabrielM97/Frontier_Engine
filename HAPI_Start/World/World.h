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
class BulletEntity;


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
	Ended = 3,
	Exit
};

class World
{
public:
	World();
	void DisplayMenu();
	void HowtoPlay(const HAPI_TKeyboardData &keyData);
	void Run();
	bool InitialiseHAPI();

	bool SetupGameWorld();
	void DisplayLogo();
	void createGameWorld();
	bool checkCollision(Entity *e);
	void CheckUserInput(Entity * e, int controllerID);
	void DeathScreen();
	void VictoryScreen();
	
	virtual ~World();
	GameState gameState = GameState::Menu;

private:
	const int SCREENWIDTH = 800;
	const int SCREENHEIGHT = 600;
	
	Graphics *window{nullptr};
	DWORD lastTick = 0;
	DWORD tick = 0;
	DWORD battleTick = 0;
	DWORD bulletTick = 0;
	unsigned int simulationTime{ 32 };
	unsigned int menuTime{ 64 };
	int currentmap;
	Sound sounds;
	int heartAnimeCount = 0;
	std::vector<PlayerEntity*> playerEntities;
	std::vector<EnemyEntity*>	enemyEntities;
	std::vector<TileMapEntity*> tileentities;
	std::vector<BulletEntity*> bulletEntites;
	std::vector<Entity*> entities;
	

};

