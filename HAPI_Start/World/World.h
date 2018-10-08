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
	void SetupGameWorld();
	void DisplayLogo();
	void createGameWorld();
	virtual ~World();

private:
	const int SCREENWIDTH = 800;
	const int SCREENHEIGHT = 600;
	Graphics *window{nullptr};
	DWORD lastTick = 0;

};

