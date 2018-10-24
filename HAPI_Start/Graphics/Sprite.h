#pragma once
#include <HAPI_lib.h>
#include "..\Rectangle.h"
#include "..\\SourceFiles\Vector2D.h"
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
enum class Direction
{
	SOUTH = 0,
	NORTH = 1,
	WEST = 2,
	EAST = 3

};
enum class State
{
	moving = 0, stop = 1, battle = 3
};

class Sprite
{
public:
	Sprite();
	Sprite(string name, int x, int y, int spritesInCol, int spritesInRow);
	void SetAttributes(string id, int texPosX, int texPosY, BYTE* data, int tw, int th, int tilesInCol, int tilesInRow );
	void Blit(BYTE * textureData, BYTE* screen, int screenWidth, int & textureWidth, int & textureHeight, float x, float y) const;
	void BlitClipping(BYTE * textureData, BYTE* screen, int screenWidth, int screenHeight, int texturePosX, int texturePosY, int textureWidth, int clippingWidth, int clippingHeight, float x, float y) const;
	void BlitWithoutAlpha(BYTE *screen, int screenWidth);
	void Draw(RenderType flag, BYTE* screen, int screenwidth, int screenheight);
	bool LoadTexture(string path);
	void Animate(Direction dir, State s);
	string GetName() { return name; };
	void SetPos(float x, float y) { position.x = x; position.y = y; };
	void SetTexturePos(float x, float y) { texturePosition.x = x; texturePosition.y = y; };
	Vector2D GetPos() { return position; };
	BYTE *GetTextureData() { return textureData; };
	int GetWidth() { return textureWidth; };
	int GetHeight() { return textureHeight; };
	Vector2D GetTexturePos() {return texturePosition;};
	bool GetIsCollidable() { return isCollidable; };
	void SetIsCollidable(bool collidable) { isCollidable = collidable; };
	void SetBounds();
	Rectangle GetBounds() { return bounds; };
	Rectangle GetCollisitionBox() { return collisionBox; };
	void CreateCollisionBox(int x, int y, int width, int height);
	void SetTextureWidthAndHeight(int w, int h) { textureWidth = w; textureHeight = h; };
	void SetTextureData(BYTE * td) { textureData = td; };
	void SetName(string newName) { name = newName; };
	void SetSpriteRowCol(int c, int r) { spritesInCol = c, spritesInRow = r; };
	int GetSpritesInRow() { return spritesInRow; };
	int GetSpritesInCol() { return spritesInCol; };
	virtual ~Sprite();

protected:
	int spritesInCol{ 0 };
	int spritesInRow{ 0 };
	string name;
	Vector2D position;
	Vector2D texturePosition;
	BYTE * textureData{ nullptr };
	int textureWidth;
	int textureHeight;
	Rectangle bounds;
	Rectangle collisionBox;
	bool isCollidable{ false };
};

