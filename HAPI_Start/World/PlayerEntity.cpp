#include "PlayerEntity.h"
#include "..\Graphics\Graphics.h"



PlayerEntity::PlayerEntity()
{
}


PlayerEntity::PlayerEntity(std::string playerName, Vector2D pos, int walkSpeed, int sprintSpeed, int w, int h,  int c_id)
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
	if (playerState == State::stop)
		position = prevPosition;

	g->Draw(spriteId.at(activeSpriteSheet), RenderType::TILE, (int)playerDirection, (int)playerState, position.x, position.y);
	prevPosition = position;
	
}

void PlayerEntity::Update()
{
	
	switch (playerDirection)
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

	switch (playerState)
	{
	case State::moving:
		SetSpeed(walkSpeed_);
		activeSpriteSheet = 0;
		break;
	case State::running:
		SetSpeed(sprintSpeed_);
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

	CreateCollisionBox(position.x, position.y, width, height );
	
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









PlayerEntity::~PlayerEntity()
{
	delete physics;
	
}
