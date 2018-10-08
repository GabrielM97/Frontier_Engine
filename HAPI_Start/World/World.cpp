#include "World.h"
#include "..\Graphics\Graphics.h"




World::World()
{
	window = new Graphics();
}

void World::Run()
{
	SetupGameWorld();
	DisplayLogo();
	createGameWorld();
}

void World::SetupGameWorld()
{
	
	
	window->CreateWindow(SCREENWIDTH, SCREENHEIGHT, "Horizon Engine", 2);

	window->CreateSprite("Lucas", 100, 100, 4, 4);
	window->LoadTexture("Lucas", "Data\\Textures\\Lucas.png");

	window->CreateSprite("logo", 0, 0, 4, 4);
	window->LoadTexture("logo", "Data\\Textures\\HorizonEngine-Logo.png");
	HAPI.SetShowFPS(true);
}

void World::DisplayLogo()
{
	time_t start = time(0);

	double seconds_since_start = 0.0;

	while (window->Update() && seconds_since_start < 2)
	{
		window->ClearScreen(34, 54, 86, 255);
		window->GetSprite("logo")->Draw(1, window);

		seconds_since_start = difftime(time(0), start);
	}

}

void World::createGameWorld()
{
	while (window->Update())
	{
		if (HAPI.GetTime() - lastTick >= 200)
		{
			window->ClearScreen(13, 153, 90, 255);

			window->GetSprite("Lucas")->Animate(Direction::NORTH, State::moving);
			window->GetSprite("Lucas")->Draw(0, window);

			lastTick = HAPI.GetTime();
		}
	}
}


World::~World()
{
	delete window;
}
