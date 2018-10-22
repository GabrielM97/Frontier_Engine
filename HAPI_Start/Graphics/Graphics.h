#pragma once
#include <HAPI_lib.h>
#include <iostream>
#include <vector>
#include <unordered_map>
#include "Sprite.h"
#include "Tileset.h"
#include "..\Rectangle.h"

using namespace std;
using namespace HAPISPACE;



class Graphics
{
public:
	Graphics();
	bool CreateWindow(const int & Width, const int & Height, string title, unsigned int flag);
	void ClearScreen(unsigned int r, unsigned int g, unsigned int b, unsigned int a);
	
	bool Update();
	void CreateSprite(std::string name, int x, int y, int spritesInCol, int spritesInRow);
	void CreateTileSet(std::string name, int tilesInCol, int tilesInRow, std::string path );
	bool LoadTexture(std::string name, std::string path)const;
	Sprite* GetSprite(std::string name) { return sprites.at(name);};
	Tileset* GetTileset(std::string name) { return tilesets.at(name); };

	void Blit(BYTE * textureData, int & textureWidth, int & textureHeight, float x, float y)const;
	void BlitClipping(BYTE * textureData, int texturePosX, int texturePosY, int textureWidth, int clippingWidth, int clippingHieght, float x, float y)const;
	virtual ~Graphics();

	
private:

	Rectangle screenRect;
	int screenWidth;
	int screenHeight;
	BYTE *screen;
	unordered_map<std::string, Sprite*> sprites;
	unordered_map<std::string, Tileset*> tilesets;


};