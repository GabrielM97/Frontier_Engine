/* 
	Horizon Game Engine! v1.1
	
	By Gabriel Menezes
*/

// Include the HAPI header to get access to all of HAPIs interfaces

#include "..\World/World.h"


// HAPI itself is wrapped in the HAPISPACE namespace


// Every HAPI program has a HAPI_Main as an entry point
// When this function exits the program will close down
void HAPI_Main()
{
	

	World *game = new World();
	
	game->Run();

	delete game;
	

	
	
	
}

