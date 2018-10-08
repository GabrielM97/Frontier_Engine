#pragma once

#include<iostream>
#include "..\SourceFiles\Vector2D.h"
#include <HAPI_lib.h>



using namespace HAPISPACE;
class Graphics;

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
	
	virtual bool LoadTexture(string path) = 0;
	virtual void Draw(int flag, Graphics *window) = 0;
	

	
};

