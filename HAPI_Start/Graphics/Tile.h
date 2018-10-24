#pragma once
#include <iostream>
#include "..\SourceFiles\Vector2D.h"
#include <HAPI_lib.h>
#include "..\\Rectangle.h"

using namespace HAPISPACE;
using namespace GM;
class Tile
{
public:

	Tile() = default;

	void SetBounds(int textureWidth, int textureHeight, int tilesInCol, int tilesInRow);
	Tile(std::string id, int x, int y, int texPosX, int texPosY, bool collidable );
	std::string GetName() { return name; };
	Vector2D getPos() { return position; };
	Vector2D getTexPos() { return texturePosition; };
	bool GetCollidable() { return isCollidable; };
	void SetCollidable(bool collidable) { isCollidable = collidable; };

	void Draw(BYTE * textureData, int textureWidth, int textureHeight, BYTE * screen, int screenwidth, int screenheight, int tilesInCol, int tilesInRow);
	void BlitClipping(BYTE * textureData, BYTE * screen, int screenWidth, int screenHeight, int texturePosX, int texturePosY, int textureWidth, int clippingWidth, int clippingHeight, float x, float y) const;
	~Tile();


private:
	std::string name;
	Vector2D position;
	Vector2D texturePosition;
	bool isCollidable{ false };
	Rectangle bounds;
};

