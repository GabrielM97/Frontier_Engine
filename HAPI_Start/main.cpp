/* 
	Horizon Game Engine! v2.2
	
	By Gabriel Menezes
*/

// Include the HAPI header to get access to all of HAPIs interfaces

#include "..\World/World.h"
#include <HAPI_lib.h>


// HAPI itself is wrapped in the HAPISPACE namespace


// Every HAPI program has a HAPI_Main as an entry point
// When this function exits the program will close down
void HAPI_Main()
{
	
	while (true)
	{
		World *game = new World();
		game->gameState = GameState::Menu;
		game->Run();

		if (game->gameState == GameState::Exit)
		{
			delete game;
			break;
		}

		delete game;

	}
	
	
}

