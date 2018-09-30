#pragma once

#include<iostream>
#include "../Vector2D.h"
#include <HAPI_lib.h>
#include "Graphics.h"


using namespace HAPISPACE;
class Entity
{
public:
	Entity();
	virtual ~Entity();

protected:

	Vector2D position;
	Vector2D texturePosition;
	BYTE * textureData{ nullptr };
	int textureWidth;
	int textureHeight;
	Graphics *renderer{ nullptr };
	virtual void Draw() = 0;
	

	
};

