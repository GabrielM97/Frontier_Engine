#pragma once
#include <iostream>
#include "Entity.h"

class BulletEntity :public Entity
{
public:


	BulletEntity(std::string bulletname, int w, int h);
	~BulletEntity();

	void Update();
	void const Render(Graphics* g);
	void CreateCollisionBox(int x, int y, int width, int height);
	void SetPosition(Vector2D pos, Direction d) { position = pos; direction = d; spawned = true; };
	Type GetType() { return entityType; };
	bool GetSpawned() { return spawned; };
	void SetSpawned(bool s) {spawned = s;};


private:
	bool spawned = false;
};

