#pragma once

#include<iostream>
#include "..\Add_On\Vector2D.h"
#include <HAPI_lib.h>
#include "..\\Add_On\Rectangle.h"
#include <iostream>



using namespace HAPISPACE;
using namespace GM;
class Graphics;
class Physics;

enum class Direction
{
	SOUTH = 0,
	NORTH = 2,
	WEST = 3,
	EAST = 1, 
	None = 4

};

enum class State
{
	moving = 0, stop = 1, battle = 3, running = 4, collided = 5
};


enum class Type
{
	Player = 0,
	Neutral = 1,
	Enemy = 3,
	Boss = 4,
	Map = 5,
	Bullet = 6
};

class Entity
{
public:

	Entity();
	virtual ~Entity();
	virtual void Update() = 0;
	virtual void const Render(Graphics* g) = 0;
	virtual void CreateCollisionBox(int x, int y, int width, int height) = 0;
	virtual Type GetType() = 0;
	virtual State GetState() { return state; };
	virtual void SetState(State s) { state = s; };
	virtual Direction GetDirection() { return direction; };
	virtual void TakeDamage(int dmg) { health -= dmg; };
	virtual bool GetIsAlive() { return isAlive; };
	virtual void SetIsAlive(bool alive) { isAlive = alive; };
	virtual string GetName() { return name; };
	virtual int GetHealth() { return health; };
	Rectangle collisionBox;
	bool isCollidable = false;
	int controllerID;

protected:
	Type entityType;
	Vector2D position, prevPosition;
	std::string name;
	Physics *physics;
	vector<std::string> spriteId;
	bool isAlive{ true };
	int walkSpeed_, sprintSpeed_, activeSpriteSheet, damage, health, max_health, height, width;
	Direction direction;
	State state;
	
	
};

