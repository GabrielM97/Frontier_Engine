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

	window->CreateSprite("Lucas", 10, 10, 4, 4);
	window->LoadTexture("Lucas", "Data\\Lucas.png");
	window->GetSprite("Lucas")->SetIsCollidable(true);

	window->CreateSprite("logo", 0, 0, 4, 4);
	window->LoadTexture("logo", "Data\\HorizonEngine-Logo.png");

	window->CreateSprite("bg", 0, 0, 4, 4);
	window->LoadTexture("bg", "Data\\Shooter.png");

	window->CreateTileSet("map1", 14, 6, "Data\\scifitiles-sheet.png");
	window->GetTileset("map1")->CreateTiles();
	window->GetTileset("map1")->GenerateTilemap();
	
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
		window->GetSprite("logo")->Draw(1, window);

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
			//window->ClearScreen(13, 153, 90, 255);
			//window->GetSprite("bg")->Draw(1, window);

			window->GetTileset("map1")->draw(window);
			CheckUserInput("Lucas");
			window->GetSprite("Lucas")->Draw(0, window);

			for (auto t : window->GetTileset("map1")->GetTile())
			{
				
				if (t.GetIsCollidable())
				{
					cout << t.GetName() << endl;
					//left intersect
					if (t.GetPos().x > window->GetSprite("Lucas")->GetPos().x &&
						t.GetPos().x < window->GetSprite("Lucas")->GetPos().x + 34)
					{

						if (t.GetPos().y > window->GetSprite("Lucas")->GetPos().y &&
							t.GetPos().y < window->GetSprite("Lucas")->GetPos().y + 34)
						{

							window->GetSprite("Lucas")->SetPos(window->GetSprite("Lucas")->GetPos().x - 5,
								window->GetSprite("Lucas")->GetPos().y);

						}

					}

					//top intersect
					if (t.GetPos().y > window->GetSprite("Lucas")->GetPos().y &&
						t.GetPos().y < window->GetSprite("Lucas")->GetPos().y + 34)
					{
						if (t.GetPos().x > window->GetSprite("Lucas")->GetPos().x &&
							t.GetPos().x < window->GetSprite("Lucas")->GetPos().x + 34)
						{

							window->GetSprite("Lucas")->SetPos(window->GetSprite("Lucas")->GetPos().x,
								window->GetSprite("Lucas")->GetPos().y - 5);

						}
					}

					if (t.GetPos().y + 30 > window->GetSprite("Lucas")->GetPos().y &&
						t.GetPos().y + 30 < window->GetSprite("Lucas")->GetPos().y + 34)
					{
						if (t.GetPos().x > window->GetSprite("Lucas")->GetPos().x &&
							t.GetPos().x < window->GetSprite("Lucas")->GetPos().x + 34)
						{


							window->GetSprite("Lucas")->SetPos(window->GetSprite("Lucas")->GetPos().x,
								window->GetSprite("Lucas")->GetPos().y + 5);

						}
					}

					if (t.GetPos().x + 30 > window->GetSprite("Lucas")->GetPos().x &&
						t.GetPos().x + 30 < window->GetSprite("Lucas")->GetPos().x + 34)
					{

						if (t.GetPos().y > window->GetSprite("Lucas")->GetPos().y &&
							t.GetPos().y < window->GetSprite("Lucas")->GetPos().y + 34)
						{

							window->GetSprite("Lucas")->SetPos(window->GetSprite("Lucas")->GetPos().x + 5,
								window->GetSprite("Lucas")->GetPos().y);

						}

					}
				}
			}


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
