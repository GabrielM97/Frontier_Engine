/* 
	Horizon Game Engine! v1.1
	
	By Gabriel Menezes
*/

// Include the HAPI header to get access to all of HAPIs interfaces
#include <HAPI_lib.h>
#include "..\World/World.h"
#include "..\Graphics/Graphics.h"
#include "..\Graphics/Sprite.h"
#include <chrono>
#include <ctime>
#include <math.h>

// HAPI itself is wrapped in the HAPISPACE namespace
using namespace HAPISPACE;
using namespace chrono;

// Every HAPI program has a HAPI_Main as an entry point
// When this function exits the program will close down
void HAPI_Main()
{
	const int SCREENWIDTH = 800;
	const int SCREENHEIGHT = 600;

	Graphics *window = new Graphics();
	Sprite *player = new Sprite(100, 100, 4, 4);
	Sprite *logo = new Sprite(0, 0, 4, 4);

	window->CreateWindow(SCREENWIDTH, SCREENHEIGHT, "Horizon Engine", 2);
	player->LoadTexture("Data\\Textures\\Lucas.png");
	logo->LoadTexture("Data\\Textures\\HorizonEngine-Logo.png");

	
	
	time_t start = time(0);
	HAPI.SetShowFPS(true);
	double seconds_since_start = 0.0;
	while (window->Update() && seconds_since_start < 2)
	{
		
		window->ClearScreen(34, 54, 86, 255);
		logo->Draw(1, window);
		
		seconds_since_start = difftime(time(0), start);
	
	}
	
	while (window->Update())
	{
		
		window->ClearScreen(255, 255, 255, 255);

		
		player->Animate(Direction::NORTH, State::moving);
		player->Draw(0, window);
			

	

	}

	delete window;
	delete player;
	delete logo;
	
}

