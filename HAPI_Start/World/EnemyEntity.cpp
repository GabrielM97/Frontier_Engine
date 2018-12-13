#include "EnemyEntity.h"
#include "..\Graphics\Graphics.h"
#include "..\Physics\Physics.h"


EnemyEntity::EnemyEntity(std::string playerName, int hp, Vector2D pos, int walkSpeed, int sprintSpeed, int w, int h)
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
	collisionBox.left = x;
	collisionBox.top = y;
	collisionBox.right = x + width;
	collisionBox.bottom = y + height;
}

void const EnemyEntity::Render(Graphics * g)
{
	if (state == State::collided)
		position -= (position - prevPosition);

	g->Draw(spriteId.at(activeSpriteSheet), RenderType::TILE, (int)direction, (int)state, position.x, position.y);
	prevPosition = position;
}

void EnemyEntity::Update()
{
	CreateCollisionBox((int)position.x, (int)position.y, width, height);
	state = State::moving;
}

EnemyEntity::~EnemyEntity()
{
	delete physics;
}
