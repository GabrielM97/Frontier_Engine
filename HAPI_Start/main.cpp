/* Frontier Game Engine!
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
	Sprite *player = new Sprite(5, 5, 4, 4);
	window->CreateWindow(SCREENWIDTH, SCREENHEIGHT, "Frontier Engine", 2);
	player->LoadSprite("Res\\Textures\\Lucas.png");
	/*BYTE *textureData;
	int textureWidth, textureHeight;
	if (!HAPI.LoadTexture("Res\\Textures\\DS DSi - Pokemon Platinum - Lucas.png", &textureData, textureWidth, textureHeight))
	{
		cerr << "Error texture not loaded correctly..." << endl;
	}

	int px = 1;
	int py = 0;*/
	while (window->Update())
	{
		window->ClearScreen(60, 88, 232, 255);
		player->Animate(Direction::SOUTH, State::moving);
		player->Draw();
		/*window->Blit(textureData, textureWidth, textureHeight, 200, 100);
		px++;

		if (px > 3)
		{
			px = 0;
		}
		window->BlitClipping(textureData, px* (textureWidth / 4), py* (textureHeight / 4),  textureWidth,
			px*(textureWidth/4)+ (textureWidth / 4), (py*(textureHeight/ 4))+ (textureHeight / 4), 400,250);*/
		HAPI.SetShowFPS(true);
	}

	delete window;
	delete player;
	
}

