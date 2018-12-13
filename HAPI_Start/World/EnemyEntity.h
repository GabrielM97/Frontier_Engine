#pragma once
#include "Entity.h"
class EnemyEntity :
	public Entity
{
public:
	EnemyEntity(std::string playerName, int hp, Vector2D pos, int walkSpeed, int sprintSpeed, int w, int h);
	void CreateCollisionBox(int x, int y, int width, int height);
	void const Render(Graphics * g);
	void Update();
	Type GetType() { return entityType; };
	~EnemyEntity();
};

