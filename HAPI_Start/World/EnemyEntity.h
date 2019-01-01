#pragma once
#include "Entity.h"
#include "..\AI\AI.h"

enum class enemyState
{
	Roam = 0,
	Alerted = 1,
	Attacking = 2
};

class EnemyEntity :
	public Entity
{
public:
	

	EnemyEntity(std::string playerName, int hp, Vector2D pos, int walkSpeed, int sprintSpeed, int awareRad, int attackRad, int w, int h);
	EnemyEntity(std::string playerName, Type t, int hp, Vector2D pos, int walkSpeed, int sprintSpeed, int awareRad, int attackRad, bool alive, int w, int h);
	void CreateCollisionBox(int x, int y, int width, int height);
	void const Render(Graphics * g);
	void const reset();
	void Update();
	void isAlerted(Vector2D playerPos);
	void setTargetPos(Vector2D pos) { targetPosition = pos; };
	bool GetTargetPosFound() { return targetPosFound; };
	void setEState(enemyState s) { eState = s; };
	enemyState GetEState() { return eState; };
	Type GetType() { return entityType; };
	void setSpawned() { spawned = true; isAlive = true; };
	bool GetSpawned() { return spawned; };
	Vector2D GetPos() { return position; };

	~EnemyEntity();
private:
	Vector2D targetPosition;
	AI ai;
	bool targetPosFound = true;
	DWORD lasttick = 0;
	int awarnessRadius;
	int attackRadius;
	enemyState eState = enemyState::Roam;
	bool spawned = false;

};

