#include "World.h"
#include "..\Graphics\Graphics.h"
#include "Entity.h"



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

	window->CreateSprite("Lucas", 100, 200, 4, 4, "Data\\player.png");

	window->GetSprite("Lucas")->SetIsCollidable(true);

	window->CreateSprite("p2", 600, 200, 4, 4, "Data\\PlayerBlue.png");

	window->GetSprite("p2")->SetIsCollidable(true);

	window->CreateSprite("logo", 0, 0, 4, 4, "Data\\HorizonEngine-Logo.png");

	window->CreateTileset("map1", 14, 6, "Data\\scifitiles-sheet.png");
	window->MakeTiles("map1");
	window->GenerateTileMap("map1");

	velocity.setPos(0, 0);
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
			window->Draw("Lucas", RenderType::TILE);
			CheckUserInput("Lucas", 0);

			window->Draw("p2", RenderType::TILE);
			//CheckUserInput("p2", 1);

			
			
			lastTick = HAPI.GetTime();
		
		}

		
	}
}
Hit World::checkCollision(std::string n1, int n2)
{
	Hit checkHit;
	
	if (window->GetSprite(n1)->GetCollisitionBox().Intersects(window->GetTiles("map1").at(n2)->GetCollisionBox()))
	{
		
		switch (window->GetSprite(n1)->dir)
		{
		case Direction::SOUTH:
			checkHit.direction = "north";
			checkHit.isHit = true;
			break;
		case Direction::NORTH:
			checkHit.direction = "south";
			checkHit.isHit = true;
			break;
		case Direction::EAST:
			checkHit.direction = "west";
			checkHit.isHit = true;
			break;
		case Direction::WEST:
			checkHit.direction = "east";
			checkHit.isHit = true;
			break;

		}
		
	}

	return checkHit;
}
#pragma endregion


#pragma region USERINPUT
void World::CheckUserInput(std::string name, int controllerID)
{
	const HAPI_TKeyboardData &keyData = HAPI.GetKeyboardData();
	bool isRunning = false;
	
	
#pragma region InputControls
#pragma region KEYBAORD INPUT

	Vector2D prevPos;
	prevPos.setPos(window->GetSprite(name)->GetPos().x - velocity.x, window->GetSprite(name)->GetPos().y - velocity.y);

	if (window->GetSprite(name)->state != State::stop)
	{
		if (keyData.scanCode[HK_DOWN])
		{

			window->GetSprite(name)->Animate(Direction::SOUTH, State::moving);
			if (!isRunning)
			{
				velocity.setPos(0, 5);
			}
			else
			{
				velocity.setPos(0, 15);
			}
			window->GetSprite(name)->dir = Direction::SOUTH;
		}
		else if (keyData.scanCode[HK_UP])
		{
			window->GetSprite(name)->Animate(Direction::NORTH, State::moving);
			if (!isRunning)
			{
				velocity.setPos(0, -5);
			}
			else
			{
				velocity.setPos(0, -15);
			}
			window->GetSprite(name)->dir = Direction::NORTH;
		}
		else if (keyData.scanCode[HK_LEFT])
		{
			window->GetSprite(name)->Animate(Direction::WEST, State::moving);
			if (!isRunning)
			{
				velocity.setPos(-5, 0);
			}
			else
			{
				velocity.setPos(-15, 0);
			}
			window->GetSprite(name)->dir = Direction::WEST;
		}
		else if (keyData.scanCode[HK_RIGHT])
		{
			window->GetSprite(name)->Animate(Direction::EAST, State::moving);
			if (!isRunning)
			{
				velocity.setPos(5, 0);
				
			}
			else
			{
				velocity.setPos(15, 0);
				
			}
			window->GetSprite(name)->dir = Direction::EAST;
		}
		else
		{
			velocity.setPos(0, 0);
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

		
		

	}


#pragma endregion
	
#pragma region ControllerInput
//TODO: Get controller input
	const HAPI_TControllerData& data = HAPI.GetControllerData(controllerID);
	if (data.isAttached)
	{
		

		double valueX = data.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X];
		double valueY = data.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y];
		

		if (valueX < -30000 )
		{
			
			window->GetSprite(name)->Animate(Direction::WEST, State::moving);
			if (!isRunning)
			{
				velocity.setPos(-5,0);
			}
			else
			{
				velocity.setPos(-15, 0);
			}
			window->GetSprite(name)->dir = Direction::WEST;
		}
		else if (valueX > 30000)
		{
			
			window->GetSprite(name)->Animate(Direction::EAST, State::moving);
			if (!isRunning)
			{
				velocity.setPos(5, 0);

			}
			else
			{
				velocity.setPos(15,0);

			}
			window->GetSprite(name)->dir = Direction::EAST;
		}else if (valueY > 30000)
		{
			
			window->GetSprite(name)->Animate(Direction::NORTH, State::moving);
			if (!isRunning)
			{
				velocity.setPos(0, -5);
			}
			else
			{
				velocity.setPos(0, -15);
			}
			window->GetSprite(name)->dir = Direction::NORTH;
		}
		else if(valueY < -30000)
		{
			
			window->GetSprite(name)->Animate(Direction::SOUTH, State::moving);
			if (!isRunning)
			{
				velocity.setPos(0, 5);
			}
			else
			{
				velocity.setPos(0, 15);
			}
			window->GetSprite(name)->dir = Direction::SOUTH;

		}

		if (data.analogueButtons[HK_ANALOGUE_RIGHT_TRIGGER] > 0)
		{
			isRunning = true;

			elaspsTime = { 50 };
		}
		else
		{
			isRunning = false;

			elaspsTime = { 100 };
		}
		
	}
#pragma endregion

	window->GetSprite(name)->SetPos(window->GetSprite(name)->GetPos().x + velocity.x, window->GetSprite(name)->GetPos().y + velocity.y);


	for (int i = 0; i < window->GetTiles("map1").size(); i++)
	{

		if (window->GetTiles("map1").at(i)->GetCollidable())
		{

			hit = checkCollision("Lucas", i);
			if (hit.isHit)
			{
				window->GetSprite(name)->SetPos(prevPos.x, prevPos.y);
				hit.isHit = false;
				break;
			}
			
				
		}

	}
#pragma endregion	
	
		
	
}
#pragma endregion




World::~World()
{
	delete window;
}
