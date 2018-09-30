#pragma once
#include "Entity.h"
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

class Sprite :public Entity
{
public:
	Sprite();

	Sprite(int x, int y, int spritesInCol, int spritesInRow);
	void Draw();
	bool LoadSprite(string path);
	void Animate(Direction dir, State s);
	virtual ~Sprite();

private:
	int spritesInCol{ 0 };
	int spritesInRow{ 0 };
};

