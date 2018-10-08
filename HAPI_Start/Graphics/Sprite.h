#pragma once
#include "..\World\Entity.h"
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

	Sprite(string name, int x, int y, int spritesInCol, int spritesInRow);
	void Draw(int flag, Graphics *window);
	bool LoadTexture(string path);
	void Animate(Direction dir, State s);
	string GetName() { return name; };
	virtual ~Sprite();

private:
	int spritesInCol{ 0 };
	int spritesInRow{ 0 };
	string name;
};

