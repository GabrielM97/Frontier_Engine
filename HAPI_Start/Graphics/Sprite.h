#pragma once
#include "..\World\Entity.h"
#include "..\Rectangle.h"
#include<string>


using namespace std;

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
	Sprite(int spritesInCol, int spritesInRow) { this->spritesInCol = spritesInCol, this->spritesInRow = spritesInRow; };
	Sprite(float tpx, float tpy, int spritesInCol, int spritesInRow) { texturePosition.x = tpx, texturePosition.y = tpy,
																	this->spritesInCol = spritesInCol, this->spritesInRow = spritesInRow;};
	Sprite(string name, int x, int y, int spritesInCol, int spritesInRow);
	void Draw(int flag, Graphics *window);
	bool LoadTexture(string path);
	void Animate(Direction dir, State s);
	string GetName() { return name; };
	void SetPos(float x, float y) { position.x = x; position.y = y; };
	Vector2D GetPos() { return position; };
	BYTE *GetTextureData() { return textureData; };
	int GetTWidth() { return textureWidth; };
	int GetTHeight() { return textureHeight; };
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

