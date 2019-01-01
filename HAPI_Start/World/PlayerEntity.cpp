#include "PlayerEntity.h"
#include "..\Graphics\Graphics.h"
#include "..\Physics\Physics.h"


PlayerEntity::PlayerEntity()
{
}


PlayerEntity::PlayerEntity(std::string playerName,int hp, Vector2D pos, int walkSpeed, int sprintSpeed, int w, int h,  int c_id)
{
	name = playerName;
	position = pos;
	prevPosition = pos;
	walkSpeed_ = walkSpeed;
	sprintSpeed_ = sprintSpeed;
	physics = new Physics();
	isCollidable = true;
	spriteId.push_back(playerName);
	activeSpriteSheet = 0;
	entityType = Type::Player;
	width = w;
	height = h;
	controllerID = c_id;
	health = hp;
	max_health = hp;
	isAlive = true;
}


void PlayerEntity::CreateCollisionBox(int x, int y, int width, int height)
{
	collisionBox.left = x;
	collisionBox.top = y;
	collisionBox.right = x + width;
	collisionBox.bottom = y + height;
}

void const PlayerEntity::Render(Graphics* g)
{
	if (state == State::collided)
		position -= (position - prevPosition);

	if (levelup)
	{
		
		time_t start = time(0);

		double seconds_since_start = 0.0;

		while (g->Update() && seconds_since_start < 2)
		{
			HAPI.RenderText(300, 200, HAPI_TColour::YELLOW, "YOU LEVELED UP!", 30);
			HAPI.RenderText(280, 240, HAPI_TColour::YELLOW, "YOU ARE NOW LEVEL " + std::to_string(lvl), 30);

			seconds_since_start = difftime(time(0), start);
		}
		levelup = false;
	}

	g->Draw(spriteId.at(activeSpriteSheet), RenderType::TILE, (int)direction, (int)state, position.x, position.y);
	prevPosition = position;
	
}

void PlayerEntity::Update()
{
	
	switch (direction)
	{

	case Direction::NORTH:
		physics->SetDirection({ 0, -1 });
		break;
	case Direction::SOUTH:
		physics->SetDirection({ 0,1 });
		break;
	case Direction::EAST:
		physics->SetDirection({ 1, 0 });
		break;
	case Direction::WEST:
		physics->SetDirection({ -1,0 });
		break;
	default:

		physics->SetDirection({ 0, 0 });
		break;
	}

	switch (state)
	{
	case State::moving:
		SetSpeed((float)walkSpeed_);
		activeSpriteSheet = 0;
		break;
	case State::running:
		SetSpeed((float)sprintSpeed_);
		break;

	case State::battle:
		activeSpriteSheet = 1;

		break;

	default:
		SetSpeed(0);
		activeSpriteSheet = 0;
		break;
	}
	

	setPosition();

	CreateCollisionBox((int)position.x, (int)position.y, width, height );
	
}

void PlayerEntity::setPosition() 
{	
	
	physics->CalcVelocity();
	position += physics->GetVelocity();

}

void PlayerEntity::SetSpeed(float updatedSpeed) 
{
	
	physics->SetSpeed(updatedSpeed);
}

void PlayerEntity::AddSpriteSheetId(std::string name)
{
	spriteId.push_back(name);
}

void PlayerEntity::gainEXP(int experience)
{
	exp += experience;
	if (exp >= expToNextLvl)
	{
		lvl++;
		exp = 0;
		expToNextLvl = expToNextLvl + 10;
		max_health += 2;
		health = max_health;

		levelup = true;
	}
}


PlayerEntity::~PlayerEntity()
{
	delete physics;
	
}
