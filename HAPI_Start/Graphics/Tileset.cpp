#include "Tileset.h"



Tileset::Tileset()
{
}

Tileset::Tileset( int tIncol, int tInRow)
{
	tilesInCol = tIncol;
	tilesInRow = tInRow;
}

bool Tileset::LoadTexture(std::string name)
{

	if (!HAPI.LoadTexture(name, &textureData, textureWidth, textureHeight))
	{
		HAPI.UserMessage("Error texture not loaded correctly...", "Error");
		
		return false;
	}

	return true;
}

void Tileset::MakeTiles()
{
    tileWidth = textureWidth / tilesInCol;
    tileHeight = textureHeight / tilesInRow;
	int id = 0;

	for (int y = 0; y < tilesInRow; y++)
	{
		for (int x = 0; x < tilesInCol; x++)
		{
			Tile * tile = new Tile(std::to_string(id), 0, 0, x, y, false);
			tileset.insert(std::pair<int, Tile*>(id, tile));
			id++;
		}
	}

}

void Tileset::CreateTileMap()
{
	int map[19][25] = {{17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17},
					   {17, 17, 17, 17, 17, 17, 17, 17, 17, 47, 48, 48, 48, 48, 48, 49, 17, 17, 17, 17, 17, 17, 17, 17, 17},
					   {17, 17, 17, 17, 17, 17, 17, 17, 47, 20, 20, 17, 18, 17, 20, 20, 49, 17, 17, 17, 17, 17, 17, 17, 17},
					   {17, 17, 17, 17, 17, 17, 17, 47, 20, 20, 20, 14, 32, 15, 20, 20, 20, 49, 17, 17, 17, 17, 17, 17, 17},
					   {17, 17, 17, 47, 48, 48, 48, 20, 20, 20, 20, 14, 32, 15, 20, 20, 20, 20, 48, 48, 48, 49, 17, 17, 17},
					   {17, 17, 47, 20, 20, 20, 20, 20, 20, 20, 20, 14, 32, 15, 20, 20, 20, 20, 20, 20, 20, 20, 49, 17, 17},
					   {17, 47, 20, 20, 20, 20, 20, 20, 20, 20, 20, 14, 32, 15, 20, 20, 20, 20, 20, 20, 20, 20, 20, 49, 17},
					   {17, 61, 20, 20, 20, 20, 20, 20, 20, 20, 20, 14, 32, 15, 20, 20, 20, 20, 20, 20, 20, 20, 20, 63, 17},
					   {17, 61, 20, 20, 20, 20, 20, 20, 20, 20, 20, 14, 32, 15, 20, 20, 20, 20, 20, 20, 20, 20, 20, 63, 17},
					   {17, 61, 20, 20, 20, 20, 20, 20, 20, 20, 20, 14, 32, 15, 20, 20, 20, 20, 20, 20, 20, 20, 20, 63, 17},
					   {17, 61, 20, 20, 20, 20, 20, 20, 20, 20, 20, 14, 32, 15, 20, 20, 20, 20, 20, 20, 20, 20, 20, 63, 17},
					   {17, 61, 20, 20, 20, 20, 20, 20, 20, 20, 20, 14, 32, 15, 20, 20, 20, 20, 20, 20, 20, 20, 20, 63, 17},
					   {17, 75, 20, 20, 20, 20, 20, 20, 20, 20, 20, 14, 32, 15, 20, 20, 20, 20, 20, 20, 20, 20, 20, 77, 17},
					   {17, 17, 75, 20, 20, 20, 20, 20, 20, 20, 20, 14, 32, 15, 20, 20, 20, 20, 20, 20, 20, 20, 77, 17, 17},
					   {17, 17, 17, 75, 76, 76, 76, 20, 20, 20, 20, 14, 32, 15, 20, 20, 20, 20, 76, 76, 76, 76, 17, 17, 17},
					   {17, 17, 17, 17, 17, 17, 17, 75, 20, 20, 20, 14, 32, 15, 20, 20, 20, 77, 17, 17, 17, 17, 17, 17, 17},
					   {17, 17, 17, 17, 17, 17, 17, 17, 75, 20, 20, 17, 18, 17, 20, 20, 77, 17, 17, 17, 17, 17, 17, 17, 17},
					   {17, 17, 17, 17, 17, 17, 17, 17, 17, 75, 76, 76, 76, 76, 76, 77, 17, 17, 17, 17, 17, 17, 17, 17, 17},
					   {17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17} 
	};

	
	for (int y = 0; y < 19; y++)
	{
		for (int x = 0; x < 25; x++)
		{
			
			if (map[y][x] == 14 || map[y][x] == 15)
			{
				tileset.at(map[y][x])->SetCollidable(true);
			}


			tilemap.push_back(new Tile(tileset.at(map[y][x])->GetName(), x * tileWidth,
				y * tileHeight, tileset.at(map[y][x])->getTexPos().x,
				tileset.at(map[y][x])->getTexPos().y, tileset.at(map[y][x])->GetCollidable()));

		}
	}
}


void Tileset::DrawTile(BYTE* screen, int screenWidth, int screemHeight)
{
	for each (Tile* t in tilemap)
	{
		t->Draw(textureData, textureWidth, textureHeight, screen, screenWidth, screemHeight, tilesInCol, tilesInRow );
	}
}


Tileset::~Tileset()
{

	delete []textureData;
	for (auto tile : tilemap)
	{
		delete tile;
	}

	for (auto t : tileset)
	{
		delete t.second;
	}
}
