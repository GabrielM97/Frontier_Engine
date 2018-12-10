#include "EnemyEntity.h"
#include "..\Graphics\Graphics.h"
#include "..\Physics\Physics.h"


EnemyEntity::EnemyEntity(std::string playerName, Vector2D pos, int walkSpeed, int sprintSpeed, int w, int h)
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
	entityType = Type::Enemy;
	width = w;
	height = h;
	
}

void EnemyEntity::CreateCollisionBox(int x, int y, int width, int height)
{
}

void const EnemyEntity::Render(Graphics * g)
{
	if (state == State::collided)
		position = prevPosition;

	g->Draw(spriteId.at(activeSpriteSheet), RenderType::TILE, (int)direction, (int)state, position.x, position.y);
	prevPosition = position;
}

void EnemyEntity::Update()
{

	CreateCollisionBox(position.x, position.y, width, height);
}

EnemyEntity::~EnemyEntity()
{
	delete physics;
}
