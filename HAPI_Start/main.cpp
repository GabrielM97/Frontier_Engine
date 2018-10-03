/* 
	Frontier Game Engine! v1.0
	
	By Gabriel Menezes
*/

// Include the HAPI header to get access to all of HAPIs interfaces
#include <HAPI_lib.h>
#include "World/World.h"
#include "Graphics/Graphics.h"
#include "Graphics/Sprite.h"
// HAPI itself is wrapped in the HAPISPACE namespace
using namespace HAPISPACE;


// Every HAPI program has a HAPI_Main as an entry point
// When this function exits the program will close down
void HAPI_Main()
{
	const int SCREENWIDTH = 800;
	const int SCREENHEIGHT = 600;

	Graphics *window = new Graphics();
	Sprite *player = new Sprite(100, 100, 4, 4);

	window->CreateWindow(SCREENWIDTH, SCREENHEIGHT, "Frontier Engine", 2);
	player->LoadTexture("Data\\Textures\\Lucas.png");

	while (window->Update())
	{
		window->ClearScreen(255, 255, 255, 255);
		player->Animate(Direction::SOUTH, State::moving);
		player->Draw(0,window);
		
		HAPI.SetShowFPS(true);
	}

	delete window;
	delete player;
	
}

