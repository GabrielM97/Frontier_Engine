#pragma once

#include <vector>
#include"Entity.h"
#include <string>

using namespace std;
class Tile: public Entity
{
public:
	
	bool LoadTexture(string path);
	void CreateTileMap();
	Tile();
	~Tile();

private:
	vector<Tile> tileMap;
};
