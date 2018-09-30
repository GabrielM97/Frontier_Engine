#pragma once
#include "Entity.h"

enum class Direction
{
	SOUTH = 0,
	NORTH = 1,
	WEST = 2,
	EAST = 3

};


class Sprite :public Entity
{
public:
	Sprite();
	
	virtual ~Sprite();

	
};

