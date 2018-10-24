#pragma once
#include <HAPI_lib.h>
#include <ctime>
#include <iostream>

class Graphics;

using namespace HAPISPACE;
using namespace std;
class World
{
public:
	World();
	void Run();
	bool SetupGameWorld();
	void DisplayLogo();
	void createGameWorld();
	void CheckUserInput(std::string name);
	virtual ~World();

private:
	const int SCREENWIDTH = 800;
	const int SCREENHEIGHT = 608;
	Graphics *window{nullptr};
	DWORD lastTick = 0;
	unsigned int elaspsTime{ 150 };

};

