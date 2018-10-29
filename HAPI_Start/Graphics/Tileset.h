#pragma once

#include <HAPI_lib.h>
#include <unordered_map>
#include <vector>
#include "Tile.h"


using namespace HAPISPACE;
class Tileset
{
public:
	Tileset();
	Tileset(int tIncol, int tInRow );
	bool LoadTexture(std::string name);
	void MakeTiles();
	void CreateTileMap();
	void DrawTile(BYTE * screen, int screenWidth, int screemHeight);
	vector<Tile*> GetTiles() { return tilemap;  };
	~Tileset();

private:
	BYTE * textureData{ nullptr };
	int textureWidth;
	int textureHeight;
	int tilesInCol;
	int tilesInRow;
	int tileWidth;
	int tileHeight;
	unordered_map<int, Tile*> tileset;
	vector<Tile*> tilemap;
};

