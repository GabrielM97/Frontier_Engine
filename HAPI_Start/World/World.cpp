
#include "World.h"
#include "..\Graphics\Graphics.h"
#include "Entity.h"
#include "PlayerEntity.h"
#include "TileMapEntity.h"
#include "EnemyEntity.h"
#include "..\\Add_On\XMLParser.h"
#include "..\Add_On\StringHandler.h"
#include "..\Sound\Sound.h"



World::World()
{
	window = new Graphics();
	
}

#pragma region Menu

void World::DisplayMenu()
{
	unordered_map<string, bool> options = { {"Play", true}, {"How to play", false}, {"Exit", false} };
	string choiceIndex[] = { "Play", "How to play", "Exit" };
	int index = 0;
	
	
	sounds.LoadSound("Data\\MENU_Pick.wav");
	
	
	while (window->Update() && gameState == GameState::Menu)
	{
		window->Draw("title", RenderType::TEXTURE, 0, 0, 0, 0);
		HAPI.ChangeFont("MingLiU-ExtB");
		int y = 200;
		
		for(auto opt : options)
		{

			switch (opt.second)
			{

			case true:
				HAPI.RenderText(5, y, HAPI_TColour::WHITE, opt.first, 50, eUnderlined);
				break;
			case false:
				HAPI.RenderText(5, y, HAPI_TColour::WHITE, opt.first, 50);
		
			}

			y += 55;
		}
		

		if (HAPI.GetTime() - lastTick >= menuTime)
		{
			const HAPI_TKeyboardData &keyData = HAPI.GetKeyboardData();

			const HAPI_TControllerData& data = HAPI.GetControllerData(0);

			double valueX = data.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X];
			double valueY = data.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y];


			if (keyData.scanCode[HK_DOWN] || valueY < -30000)
			{
				options.at(choiceIndex[index]) = false;
				index++;
				if (index > 2)
					index = 0;
				options.at(choiceIndex[index]) = true;

				
				sounds.PlaySound("Data\\MENU_Pick.wav", 1);
				sounds.ModifySoundSettings(1, false, 0.5f);
			}
			else if (keyData.scanCode[HK_UP] || valueY > 30000)
			{
				options.at(choiceIndex[index]) = false;
				index--;
				if (index < 0)
					index = 2;
				options.at(choiceIndex[index]) = true;
				
				sounds.PlaySound("Data\\MENU_Pick.wav", 1);
				sounds.ModifySoundSettings(1, false, 0.5f);
			}
			
			
			if (keyData.scanCode['A'] || data.digitalButtons[HK_DIGITAL_A])
			{

			}
			lastTick = HAPI.GetTime();
		}


	}
}
#pragma endregion


#pragma region SETUP
void World::Run()
{
	if (!SetupGameWorld())
		return;

	DisplayLogo();
	sounds.PlayStreamedSounds("Data\\The Fall of Arcana.wav", 2);
	sounds.ModifySoundSettings(2, true, 1);
	DisplayMenu();

	switch (gameState)
	{

	case GameState::InGame:
		createGameWorld();
		break;
	
	case GameState::Ended:
		return;
		break;
	
	}
	
}

bool World::SetupGameWorld()
{

	if (!window->CreateWindow(SCREENWIDTH, SCREENHEIGHT, "Horizon Engine", 2))
	{
		return false;
	}

	window->CreateSprite("Lucas",  4, 4, "Data\\character.png");
	window->CreateSprite("Log",  3, 4, "Data\\monster_bird1.png");
	window->CreateSprite("battle",  4, 4, "Data\\characterBattle.png");
	
	enemyEntities.push_back(new EnemyEntity("Log",3, { 250,200 }, 2, 4, 50, 40));
	playerEntities.push_back(new PlayerEntity("Lucas",3, { 200,200 }, 2, 4, 14, 24, 0));
	playerEntities.at(0)->AddSpriteSheetId("battle");

	window->CreateSprite("logo",  4, 4, "Data\\HorizonEngine-Logo.png");
	window->CreateSprite("title",  4, 4, "Data\\TitleScreen.png");
	window->CreateSprite("map1",  40, 36, "Data\\Overworld.png");

	tileentities.push_back(new TileMapEntity("map1", 40, 36, 640, 576 ));
	tileentities.at(0)->MakeTile();
	tileentities.at(0)->CreateTileMap();

	entities.push_back(tileentities.at(0));
	entities.push_back(enemyEntities.at(0));
	entities.push_back(playerEntities.at(0));
	
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
		window->Draw("logo", RenderType::TEXTURE, 0, 0, 0, 0);

		seconds_since_start = difftime(time(0), start);
	}

}
#pragma endregion;


#pragma region GAME
void World::createGameWorld()
{

	while (window->Update())
	{

		if (HAPI.GetTime() - lastTick >= simulationTime)
		{
			for (auto *e : entities)
			{
				
				if(e->GetType() == Type::Player)
					CheckUserInput(e, e->controllerID);

				e->Update();

				if (checkCollision(e)) 
				{
					e->SetState(State::collided);
				}

				e->Render(window);
				
			}

			lastTick = HAPI.GetTime();
		}

	}
}


#pragma endregion

#pragma region Collisiions
bool World::checkCollision(Entity * e)
{

	for (auto *entity : entities)
	{

		if (entity->GetType() == Type::Map)
		{
			TileMapEntity * m = (TileMapEntity*)entity;
			for (auto & t : m->getTile())
			{
				if (t->isCollidable && e->isCollidable)
				{
					if (e->collisionBox.Intersects(t->collisionBox))
					{
						cout << " Collision t" << endl;
						return true;
					}
						
				}
			}
		}
		else
		{
			if (entity->isCollidable && e->isCollidable  && e != entity)
			{
				if (e->collisionBox.Intersects(entity->collisionBox))
				{
					return true;
				}
					
			}
		}

	}
	return false;
}
#pragma endregion

#pragma region USERINPUT
void World::CheckUserInput(Entity *e, int controllerID)
{
	PlayerEntity* player = (PlayerEntity*)e;
	const HAPI_TKeyboardData &keyData = HAPI.GetKeyboardData();

	const HAPI_TControllerData& data = HAPI.GetControllerData(controllerID);

	double valueX = data.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X];
	double valueY = data.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y];

	if (keyData.scanCode[HK_SPACE] || data.analogueButtons[HK_ANALOGUE_RIGHT_TRIGGER] > 0)
	{
		player->SetState(State::running);
	}
	else
	{
		player->SetState(State::moving);
	}

	if (keyData.scanCode[HK_DOWN] || valueY < -30000)
	{
		player->SetDirection(Direction::SOUTH);
	}
	else if (keyData.scanCode[HK_UP] || valueY > 30000)
	{
		player->SetDirection(Direction::NORTH);
	}
	else if (keyData.scanCode[HK_LEFT] || valueX < -30000)
	{
		player->SetDirection(Direction::WEST);
	}
	else if (keyData.scanCode[HK_RIGHT] || valueX > 30000)
	{
		player->SetDirection(Direction::EAST);
	}
	else
	{
		if (player->GetState() != State::battle)
			player->SetState(State::stop);
	}

	if (keyData.scanCode['X'] || data.digitalButtons[HK_DIGITAL_X])
	{
		player->SetState(State::battle);
	}

}


#pragma endregion

World::~World()
{

	for (auto e : entities)
		delete e;

	delete window;
}
