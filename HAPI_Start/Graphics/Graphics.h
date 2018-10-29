#pragma once
#include <HAPI_lib.h>
#include <iostream>
#include <vector>
#include <unordered_map>
#include "Sprite.h"
#include "..\Rectangle.h"
#include "Tileset.h"

using namespace std;
using namespace HAPISPACE;

class Tile;

class Graphics
{
public:
	Graphics();
	bool CreateWindow(const int & Width, const int & Height, string title, unsigned int flag);
	void ClearScreen(unsigned int r, unsigned int g, unsigned int b, unsigned int a);
	
	bool Update();
	bool CreateSprite(std::string name, int x, int y, int spritesInCol, int spritesInRow, std::string path);

	bool CreateTileset(std::string name, int spritesInCol, int spritesInRow, std::string path);

	void MakeTiles(std::string name);
	void GenerateTileMap(std::string name);
	void DrawTilemap(std::string name);

	Sprite* GetSprite(std::string name) { return sprites.at(name);};
	Tileset* GetTileSet(std::string name) { return tilesets.at(name);};
	vector<Tile*> GetTiles(std::string name) { return tilesets.at(name)->GetTiles(); };

	void Draw(std::string name, RenderType flag);
	
	virtual ~Graphics();

	
private:

	Rectangle screenRect;
	int screenWidth;
	int screenHeight;
	BYTE *screen;
	unordered_map<std::string, Sprite*> sprites;
	unordered_map<std::string, Tileset*> tilesets;



};