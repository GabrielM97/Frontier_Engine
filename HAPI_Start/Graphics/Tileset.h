#pragma once

#include <vector>
#include "Sprite.h"
#include <string>
#include <unordered_map>



using namespace std;


class Tileset
{
public:
	
	bool LoadTexture(string path);
	void CreateTiles();
	Tileset() = default;
	Tileset(int tilesInX, int tilesInY) : tilesInCol(tilesInX), tilesInRow(tilesInY) {};
	void draw(Graphics * window);
	vector<Sprite> GetTile() { return tilemap; };
	void GenerateTilemap();
	~Tileset();

private:
	int tileWidth;
	int tileHeight;
	int tilesInCol;
	int tilesInRow;
	BYTE * Data{ nullptr };
	int textureWidth;
	int textureHeight;
	unordered_map<int , Sprite*> tiles;
	vector<Sprite> tilemap;
};

