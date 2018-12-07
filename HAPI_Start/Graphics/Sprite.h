#pragma once
#include <HAPI_lib.h>
#include "..\\Add_On\Rectangle.h"
#include "..\\Add_On\Vector2D.h"
#include<string>


using namespace std;
using namespace HAPISPACE;
using namespace GM;


enum class RenderType
{
	TILE = 0,
	TEXTURE =1,
	NO_ALPHA = 3
};



class Sprite
{
public:
	
	Sprite();
	Sprite(string name, int spritesInCol, int spritesInRow);

	void Blit(BYTE * textureData, BYTE* screen, int screenWidth, int & textureWidth, int & textureHeight, float x, float y) const;
	void BlitClipping(BYTE * textureData, BYTE* screen, int screenWidth, int screenHeight, int texturePosX, int texturePosY, int textureWidth, int clippingWidth, int clippingHeight, float x, float y) const;
	void BlitWithoutAlpha(BYTE * screen, int screenWidth, float posX, float posY);
	void Draw(RenderType flag, BYTE* screen, int screenwidth, int screenheight, float posX, float posY);
	void Draw(RenderType flag, BYTE * screen, int screenwidth, int screenheight, float posX, float posY, Vector2D texturePos);
	bool LoadTexture(string path);
	void Animate(int dir, int s);
	void SetBounds();

	void SetBounds(Vector2D texturePos);
	
	virtual ~Sprite();

protected:
	int spritesInCol{ 0 };
	int spritesInRow{ 0 };
	string name;
	Vector2D texturePosition;
	BYTE * textureData{ nullptr };
	int textureWidth;
	int textureHeight;
	Rectangle bounds;
	
	
};

