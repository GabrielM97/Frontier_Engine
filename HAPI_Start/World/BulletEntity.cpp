#include "BulletEntity.h"
#include "..\Graphics\Graphics.h"



BulletEntity::BulletEntity(std::string bulletname, int w, int h)
{

	name = bulletname;
	width = w;
	height = h;
	entityType = Type::Bullet;
	position.setPos( 300, 200 );
	walkSpeed_ = 15;
	isAlive = false;
	isCollidable = true;

}

BulletEntity::~BulletEntity()
{
}



void BulletEntity::Update()
{
	switch (direction)
	{
	case Direction::SOUTH:
		position += {0, (float)walkSpeed_};
		break;
	case Direction::NORTH:
		position += {0, (float)-walkSpeed_};
		break;
	case Direction::WEST:
		position += {(float)-walkSpeed_, 0};
		break;
	case Direction::EAST:
		position += {(float)walkSpeed_, 0};
		break;
	
	}

	CreateCollisionBox(position.x+(width/2), position.y, width, height);

	if (position.y > 600)
		isAlive = false;
	
}

void const BulletEntity::Render(Graphics* g)
{
	g->Draw(name, RenderType::TILE, (int)direction, (int)state, position.x, position.y);
	
}

void BulletEntity::CreateCollisionBox(int x, int y, int width, int height) 
{
	collisionBox.left = x;
	collisionBox.top = y;
	collisionBox.right = x + width;
	collisionBox.bottom = y + height;
}