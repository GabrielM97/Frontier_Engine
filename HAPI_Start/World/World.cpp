
#include "World.h"
#include "..\Graphics\Graphics.h"
#include "Entity.h"
#include "PlayerEntity.h"
#include "TileMapEntity.h"
#include "EnemyEntity.h"
#include "..\\Add_On\XMLParser.h"
#include "..\Add_On\StringHandler.h"
#include "..\Sound\Sound.h"
#include "BulletEntity.h"
#include <time.h>
#include <math.h>


World::World()
{
	window = new Graphics();

	
}

#pragma region Menu

void World::DisplayMenu()
{
	unordered_map<string, bool> options = { {"Play", true}, {"Controls", false}, {"Exit", false} };
	string choiceIndex[] = { "Play", "Controls", "Exit" };

	int index = 0;

	while (window->Update() && gameState == GameState::Menu)
	{
		const HAPI_TKeyboardData &keyData = HAPI.GetKeyboardData();
		const HAPI_TControllerData& data = HAPI.GetControllerData(0);
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
				sounds.ModifySoundSettings(1, false, 0.0f);
			}
			else if (keyData.scanCode[HK_UP] || valueY > 30000)
			{
				options.at(choiceIndex[index]) = false;
				index--;
				if (index < 0)
					index = 2;
				options.at(choiceIndex[index]) = true;
				
				sounds.PlaySound("Data\\MENU_Pick.wav", 1);
				sounds.ModifySoundSettings(1, false, 0.0f);
			}
			
			lastTick = HAPI.GetTime();
		}

		if (keyData.scanCode[HK_RETURN] || data.digitalButtons[HK_DIGITAL_A])
		{
			sounds.PlaySound("Data\\MENU A_Select.wav", 3);
			sounds.ModifySoundSettings(3, false, 0.5f);
			for (auto& opt : options)
			{
				if (opt.first == choiceIndex[0] && opt.second)
				{
					gameState = GameState::InGame;
					sounds.StopStreamedSounds(2);
					sounds.StopSound(2);
					sounds.StopSound(3);
				}
				else if (opt.first == choiceIndex[1] && opt.second)
				{
					//options.at(choiceIndex[index]) = false;
					HowtoPlay(keyData);
				}
				else if (opt.first == choiceIndex[2] && opt.second)
					gameState = GameState::Exit;
			}
		}
	}
}

void World::HowtoPlay(const HAPI_TKeyboardData &keyData)
{

	string text[] = {
					"Keyboard:",
					"    Move-> Arrow keys",
					"    Run-> Spacebar",
					"    Select-> Enter",
					"    Back-> esc",
					"    Attacking-> X",
					"",
					"Controller:",
					"    Move->Left analogue stick",
					"    Run->Right Trigger",
					"    Select-> A",
					"    Back-> B",
					"    Attacking-> X",
	};
	bool inloop = true;

	while (window->Update() && inloop)
	{
		const HAPI_TControllerData& data = HAPI.GetControllerData(0);

		int x = 100, y = 200;
		window->Draw("htp", RenderType::TEXTURE, 0, 0, 0, 0);
		HAPI.RenderText(300, 100, HAPI_TColour::WHITE, "Controls", 40);

		for each (auto& line in text)
		{

			if (line == "Keyboard" || line == "Controller")
				HAPI.RenderText(x, y, HAPI_TColour::WHITE, line, 30, eUnderlined);
			else if (line != "")
				HAPI.RenderText(x, y, HAPI_TColour::WHITE, line, 25);
			else
			{
				x = 400;
				y = 170;
			}

			y += 30;
		}

		if (keyData.scanCode[HK_ESCAPE] || data.digitalButtons[HK_DIGITAL_B])
		{
			sounds.PlaySound("Data\\MENU A - Back.wav", 4);
			sounds.ModifySoundSettings(4, false, 0.5f);
			inloop = false;
		}
	}
}
#pragma endregion

#pragma region SETUP



void World::Run()
{
	InitialiseHAPI();
	
	if (!SetupGameWorld())
		return;

	sounds.PlayStreamedSounds("Data\\The Fall of Arcana.wav", 2);
	sounds.ModifySoundSettings(2, true, 0);
	DisplayLogo();
	DisplayMenu();
	createGameWorld();
	if (!window->Update())
		gameState = GameState::Exit;

	
	
}

bool World::InitialiseHAPI()
{

	if (!window->CreateWindow(SCREENWIDTH, SCREENHEIGHT, "Horizon Engine", 2))
	{
		return false;
	}
	return true;
	
}


bool World::SetupGameWorld()
{
	currentmap = 0;

	srand((int)time(NULL));

	sounds.LoadSound("Data\\MENU_Pick.wav");
	sounds.LoadSound("Data\\MENU A - Back.wav");
	sounds.LoadSound("Data\\MENU A_Select.wav");
	sounds.LoadSound("Data\\orchestra.wav");
	sounds.LoadSound("Data\\swing2.wav");
	sounds.LoadSound("Data\\knifesharpener1.flac");

	window->CreateSprite("Arthur",  4, 4, "Data\\character.png");
	window->CreateSprite("bird",  3, 4, "Data\\monster_bird1.png");
	window->CreateSprite("log",  3, 4, "Data\\log.png");
	window->CreateSprite("battle",  4, 4, "Data\\characterBattle.png");
	window->CreateSprite("mage",  3, 4, "Data\\$monster_lich.png");
	window->CreateSprite("ben", 1, 1, "Data\\Ben.png");
	window->CreateSprite("heart", 5, 1, "Data\\Heart.png");
	window->CreateSprite("logo", 4, 4, "Data\\HorizonEngine-Logo.png");
	window->CreateSprite("title", 4, 4, "Data\\TitleScreen.png");
	window->CreateSprite("hud", 4, 4, "Data\\hud.png");
	window->CreateSprite("hue", 4, 4, "Data\\bluehue.png");
	window->CreateSprite("htp", 4, 4, "Data\\howtoplaymenu.png");
	window->CreateSprite("map1", 40, 36, "Data\\Overworld.png");
	window->CreateSprite("map2", 19, 13, "Data\\sheet.png");
	window->CreateSprite("bossAtk", 1, 1, "Data\\BossAtk.png");

	
	
	enemyEntities.push_back(new EnemyEntity("bird",10, { 250,200 }, 2, 5, 120, 80, 50, 40));
	enemyEntities.push_back(new EnemyEntity("log",3, { 250,300 }, 3, 8, 100, 50, 14, 24));
	enemyEntities.push_back(new EnemyEntity("mage", Type::Boss, 50, { 400,50 }, 50, 15, 250, 300, false, 64, 100));
	playerEntities.push_back(new PlayerEntity("Arthur",20, { 200,200 }, 2, 4, 14, 24, 0));
	//playerEntities.push_back(new PlayerEntity("ben",3, { 200,150 }, 2, 4, 14, 24, 1));
	playerEntities.at(0)->AddSpriteSheetId("battle");


	tileentities.push_back(new TileMapEntity("map1", 40, 36, 640, 576 ));
	tileentities.push_back(new TileMapEntity("map2", 19, 13, 304, 208 ));
	tileentities.at(0)->MakeTile();
	tileentities.at(0)->CreateTileMap("Data\\testmap.xml");

	tileentities.at(1)->MakeTile();
	tileentities.at(1)->CreateTileMap("Data\\Dungeon.xml");

	bulletEntites.push_back(new BulletEntity("bossAtk", 50, 50));

	
	entities.push_back(tileentities.at(currentmap));
	
	entities.push_back(enemyEntities.at(0));
	entities.push_back(enemyEntities.at(1));
	entities.push_back(playerEntities.at(0));

	
	HAPI.SetShowFPS(true);
	return true;
}


void World::DisplayLogo()
{
	time_t start = time(0);

	double seconds_since_start = 0.0;

	while (window->Update() && seconds_since_start <3)
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
	sounds.PlayStreamedSounds("Data\\Journey to the East Rocks.ogg", 4);
	while (window->Update() && gameState == GameState::InGame)
	{
		// sets the map to draw based on the currentmap id
		entities.at(0) = tileentities.at(currentmap);

		if (HAPI.GetTime() - tick >= 10000 && currentmap == 0 )
		{
			for (auto *enemy : enemyEntities)
			{
				if (!enemy->GetIsAlive() && enemy->GetType() != Type::Boss)
				{
					enemy->reset();
					enemy->Update();
					while (checkCollision(enemy))
					{
						enemy->reset();
						enemy->Update();
					}
						
					
					entities.push_back(enemy);
				}

			}
			tick = HAPI.GetTime();
		}
		
		
		for (auto *enemy : enemyEntities)
		{

			if (currentmap == 1 && enemy->GetType() == Type::Boss && !enemy->GetSpawned())
			{
				entities.push_back(enemy);
				enemy->setSpawned();
				
			}
		}

		if (HAPI.GetTime() - lastTick >= simulationTime)
		{

			int index = 0;
			for (auto *e : entities)
			{

				if (e->GetType() == Type::Player)
				{
					int x = 30;
					CheckUserInput(e, e->controllerID);
					int totalhearts = (e->GetHealth() / 4);
					window->Draw("hud",RenderType::TEXTURE, 0,0,5,20);
					PlayerEntity *p = (PlayerEntity*)e;
					HAPI.RenderText(x, 75, HAPI_TColour::BLACK, p->GetName());
					HAPI.RenderText(x, 105, HAPI_TColour::BLACK, "Level: " + std::to_string(p->GetLevel()));
					HAPI.RenderText(x, 120, HAPI_TColour::BLACK, "EXP: " + std::to_string(p->GetExp()) + " / " + std::to_string(p->GetExpToNextLevel()));

					for (int i = 0; i < totalhearts; i++)
					{
						
						if (i == totalhearts -1)
							window->Draw("heart", RenderType::TILE, 0, 1, x-3, 90, { (float)heartAnimeCount, 0.0f });
						else
							window->Draw("heart", RenderType::TILE, 0, 1, x-3, 90, { 0.0f, 0.0f });


						x += 25;
					}

					if (totalhearts == 0)
					{
						
						if (currentmap == 0)
							sounds.StopStreamedSounds(4);
						else
							sounds.StopStreamedSounds(7);

						window->ClearScreen(0, 0, 0, 0);
						sounds.PlayStreamedSounds("Data\\Death Is Just Another Path.wav", 6);
						DeathScreen();
						gameState = GameState::Ended;
						return;
					}
						

				}
				
				if (e->GetType() == Type::Enemy || e->GetType() == Type::Boss)
				{
					EnemyEntity * enemy = (EnemyEntity*)e;
					if (enemy->GetTargetPosFound())
					{
						float x = (float)(rand() % 400) + 200;
						float y = (float)(rand() % 300) + 200;

						enemy->setTargetPos({ x, y });

						
					}

					enemy->isAlerted(playerEntities[0]->GetPosition());

					if (enemy->GetType() == Type::Boss && enemy->GetEState() == enemyState::Attacking && !bulletEntites[0]->GetSpawned())
					{
						bulletEntites[0]->SetPosition({ enemy->GetPos().x+25, enemy->GetPos().y  }, Direction::SOUTH);
						bulletEntites[0]->SetIsAlive(true);
						entities.push_back(bulletEntites[0]);

					}

					if (!e->GetIsAlive())
					{
						entities.erase(entities.begin() + index);
						playerEntities[0]->gainEXP(20);
						if (playerEntities[0]->GetLevelUP())
						{
							sounds.PlaySound("Data\\orchestra.wav", 4);
						}

						if (e->GetType() == Type::Boss)
						{
							
							sounds.StopStreamedSounds(7);

							window->ClearScreen(0, 0, 0, 0);
							sounds.PlayStreamedSounds("Data\\Lively Meadow Victory and Song Loop A (Plays ONCE).wav", 7);
							VictoryScreen();
							gameState = GameState::Ended;
							return;
						}
					}
				}

				e->Update();


				if (checkCollision(e))
				{
					e->SetState(State::collided);
				}


				if (e->GetType() == Type::Bullet)
				{
					if (!e->GetIsAlive())
					{
						bulletEntites[0]->SetSpawned(false);
						entities.erase(entities.begin() + index);
					}
						

				}
				e->Render(window);

				index++;
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
						if (t->name == "351" && e->GetType() == Type::Player)
						{
							currentmap = 1;
							PlayerEntity *p = (PlayerEntity*)e;
							p->setprevPosition({350, 550});
							sounds.StopStreamedSounds(4);
							sounds.PlayStreamedSounds("Data\\old city theme.ogg", 7);
							
						}
						
						if (entity->GetType() == Type::Bullet)
						{
							
							entity->SetIsAlive(false);
						}
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
					
					if (e->GetType() == Type::Player)
					{

						if (e->GetState() == State::battle)
						{
							entity->TakeDamage(1);
						}
					}

					if (e->GetType() == Type::Enemy )
					{

						if (HAPI.GetTime() - battleTick >= 1000)
						{
							EnemyEntity *enemy = (EnemyEntity*)e;

							if (enemy->GetEState() == enemyState::Attacking)
							{
								entity->TakeDamage(1);
								heartAnimeCount = 4 - (entity->GetHealth() % 4);
							}

							battleTick = HAPI.GetTime();
						}

						
						
					}

					if (e->GetType() == Type::Bullet && entity->GetType() == Type::Player)
					{
						entity->TakeDamage(4);
						heartAnimeCount = 4 - (entity->GetHealth() % 4);
						e->SetIsAlive(false);
					}
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
		{
			player->SetState(State::stop);
			HAPI.SetControllerRumble(0, 0, 0);
		}
		

	}

	if (keyData.scanCode['X'] || data.digitalButtons[HK_DIGITAL_X])
	{
		sounds.PlaySound("Data\\knifesharpener1.flac",5);
		HAPI.SetControllerRumble(0, 10000, 10000);
		player->SetState(State::battle);
	}

}
#pragma endregion

void World::DeathScreen()
{
	HAPI.SetControllerRumble(0, 0, 0);
	bool end = false;
	
	while (window->Update() && !end)
	{
		window->ClearScreen(142, 17, 17, 255);
		HAPI.RenderText(290, 100, HAPI_TColour::BLACK, "YOU DIED!", 50);
		HAPI.RenderText(180, 160, HAPI_TColour::BLACK, "You have subcome to the darkness", 30);
		HAPI.RenderText(270, 200, HAPI_TColour::BLACK, "Better luck next time!", 30);
		HAPI.RenderText(320, 240, HAPI_TColour::BLACK, "Thanks for playing!", 20);
		HAPI.RenderText(260, 500, HAPI_TColour::BLACK, "Press 'esc'/'B' to exit", 25);
		HAPI.RenderText(5, 570, HAPI_TColour::BLACK, "Last Dream, By Gabriel Menezes", 20);
		const HAPI_TKeyboardData &keyData = HAPI.GetKeyboardData();
		const HAPI_TControllerData& data = HAPI.GetControllerData(0);
		if (keyData.scanCode[HK_ESCAPE] || data.digitalButtons[HK_DIGITAL_B])
		{
			
			end = true;
		}

		sounds.StopStreamedSounds(6);
	}

}

void World::VictoryScreen()
{
	HAPI.SetControllerRumble(0, 0, 0);
	bool end = false;

	while (window->Update() && !end)
	{
		window->ClearScreen(85, 237, 47, 255);
		HAPI.RenderText(1300, 100, HAPI_TColour::BLACK, "YOU'VE KILLED THE MAGE!", 50);
		HAPI.RenderText(200, 160, HAPI_TColour::BLACK, "You have overcome the darkness", 30);
		HAPI.RenderText(260, 200, HAPI_TColour::BLACK, "And have beaten the game!", 25);
		HAPI.RenderText(320, 240, HAPI_TColour::BLACK, "Thanks for playing!", 20);
		HAPI.RenderText(260, 500, HAPI_TColour::BLACK, "Press 'esc'/'B' to exit", 25);
		HAPI.RenderText(5, 570, HAPI_TColour::BLACK, "Last Dream, By Gabriel Menezes", 20);
		const HAPI_TKeyboardData &keyData = HAPI.GetKeyboardData();
		const HAPI_TControllerData& data = HAPI.GetControllerData(0);
		if (keyData.scanCode[HK_ESCAPE] || data.digitalButtons[HK_DIGITAL_B])
		{

			end = true;
			sounds.StopStreamedSounds(7);
		}
	}
	
}

World::~World()
{
	for (auto *enemy : enemyEntities)
	{
		if (!enemy->GetIsAlive())
		{
			enemy->reset();
			
			entities.push_back(enemy);
		}
	}
	
	if (currentmap == 0)
	{
		entities.push_back(tileentities.at(1));
	}
	else
	{
		entities.push_back(tileentities.at(0));
		
	}
	
	if(!bulletEntites[0]->GetSpawned())
		entities.push_back(bulletEntites[0]);

	for (auto e : entities)
		delete e;

	

	delete window;
}
