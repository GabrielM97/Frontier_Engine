#include "World.h"
#include "..\Graphics\Graphics.h"




World::World()
{
	window = new Graphics();
	
}


#pragma region SETUP
void World::Run()
{
	if (!SetupGameWorld())
		return;
	DisplayLogo();
	createGameWorld();
}



bool World::SetupGameWorld()
{
	
	
	if (!window->CreateWindow(SCREENWIDTH, SCREENHEIGHT, "Horizon Engine", 2))
	{
		return false;
	}

	window->CreateSprite("Lucas", 10, 10, 4, 4, "Data\\Lucas.png");

	window->GetSprite("Lucas")->SetIsCollidable(true);

	window->CreateSprite("logo", 0, 0, 4, 4, "Data\\HorizonEngine-Logo.png");

	window->CreateTileset("map1", 14, 6, "Data\\scifitiles-sheet.png");
	window->MakeTiles("map1");
	window->GenerateTileMap("map1");
	HAPI.SetShowFPS(true);
	return true;
}

void World::DisplayLogo()
{
	time_t start = time(0);

	double seconds_since_start = 0.0;

	while (window->Update() && seconds_since_start <4)
	{
		window->ClearScreen(34, 54, 86, 255);
		window->Draw("logo", RenderType::TEXTURE);

		seconds_since_start = difftime(time(0), start);
	}

}
#pragma endregion;


#pragma region GAME
void World::createGameWorld()
{

	while (window->Update())
	{
		if (HAPI.GetTime() - lastTick >= elaspsTime)
		{
			window->DrawTilemap("map1");
			CheckUserInput("Lucas");
			window->Draw("Lucas", RenderType::TILE);


			lastTick = HAPI.GetTime();
		
		}

		
	}
}
#pragma endregion

#pragma region USERINPUT
void World::CheckUserInput(std::string name)
{
	const HAPI_TKeyboardData &keyData = HAPI.GetKeyboardData();
	bool isRunning = false;


#pragma region KEYBAORD INPUT
	if (keyData.scanCode[HK_DOWN])
	{
		
		window->GetSprite(name)->Animate(Direction::SOUTH, State::moving);
		if (isRunning)
		{
			window->GetSprite(name)->SetPos(window->GetSprite(name)->GetPos().x, window->GetSprite(name)->GetPos().y + 15);
		}
		else
		{
			window->GetSprite(name)->SetPos(window->GetSprite(name)->GetPos().x, window->GetSprite(name)->GetPos().y + 5);
		}
		
	}
	else if (keyData.scanCode[HK_UP])
	{
		window->GetSprite(name)->Animate(Direction::NORTH, State::moving);
		if (isRunning)
		{
			window->GetSprite(name)->SetPos(window->GetSprite(name)->GetPos().x, window->GetSprite(name)->GetPos().y - 15);
		}
		else
		{
			window->GetSprite(name)->SetPos(window->GetSprite(name)->GetPos().x, window->GetSprite(name)->GetPos().y - 5);
		}
	}
	else if (keyData.scanCode[HK_LEFT])
	{
		window->GetSprite(name)->Animate(Direction::WEST, State::moving);
		if (isRunning)
		{
			window->GetSprite(name)->SetPos(window->GetSprite(name)->GetPos().x-15, window->GetSprite(name)->GetPos().y );
		}
		else
		{
			window->GetSprite(name)->SetPos(window->GetSprite(name)->GetPos().x -5, window->GetSprite(name)->GetPos().y );
		}
	}
	else if (keyData.scanCode[HK_RIGHT])
	{
		window->GetSprite(name)->Animate(Direction::EAST, State::moving);
		if (isRunning)
		{
			window->GetSprite(name)->SetPos(window->GetSprite(name)->GetPos().x + 15, window->GetSprite(name)->GetPos().y);
		}
		else
		{
			window->GetSprite(name)->SetPos(window->GetSprite(name)->GetPos().x + 5, window->GetSprite(name)->GetPos().y);
		}
	}

	if (keyData.scanCode[HK_SPACE])
	{
		isRunning = true;
		elaspsTime = { 50 };
	}
	else
	{
		isRunning = false;
		elaspsTime = { 100 };
	}
#pragma endregion



//TODO: Get controller input



}
#pragma endregion

World::~World()
{
	delete window;
}
