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
		HAPI.UserMessage("Error texture not loaded correctly...\nPath:"+name, "Error");
		HAPI.Close();
		return false;
	}

	return true;
}

void Tileset::MakeTiles()
{
    tileWidth = textureWidth / tilesInCol;
    tileHeight = textureHeight / tilesInRow;
	int id = 1;

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

		
	int map[19][25] = { {18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18},
						{18,18,18,18,18,18,18,18,21,21,21,21,21,21,21,21,21,18,18,18,18,18,18,18,18},
						{18,18,18,18,18,18,18,21,21,21,21,21,21,21,21,21,21,21,18,18,18,18,18,18,18},
						{18,18,18,18,18,18,21,21,21,21,21,15,33,16,21,21,21,21,21,18,18,18,18,18,18},
						{18,18,18,18,21,21,21,35,35,21,21,15,33,16,21,21,35,35,21,21,21,18,18,18,18},
						{18,18,21,21,21,21,22,18,18,20,21,15,33,16,21,22,18,18,20,21,21,21,21,18,18},
						{18,18,21,21,21,21,22,18,18,20,21,21,21,21,21,22,18,18,20,21,21,21,21,18,18},
						{18,18,21,21,21,21,21, 7, 7,21,21,21,21,21,21,21, 7, 7,21,21,21,21,21,18,18},
						{18,18,21,21,21,21,21,21,21,21,21,15,33,16,21,21,21,21,21,21,21,21,21,18,18},
						{18,18,21,21,21,21,21,21,21,21,21,15,33,16,21,21,21,21,21,21,21,21,21,18,18},
						{18,18,21,21,21,21,21,21,21,21,21,15,33,16,21,21,21,21,21,21,21,21,21,18,18},
						{18,18,21,21,21,21,21,35,35,21,21,21,21,21,21,21,35,35,21,21,21,21,21,18,18},
						{18,18,21,21,21,21,22,18,18,20,21,21,21,21,21,22,18,18,20,21,21,21,21,18,18},
						{18,18,21,21,21,21,22,18,18,20,21,15,33,16,21,22,18,18,20,21,21,21,21,18,18},
						{18,18,18,18,21,21,21, 7, 7,21,21,15,33,16,21,21, 7, 7,21,21,21,18,18,18,18},
						{18,18,18,18,18,18,21,21,21,21,21,15,33,16,21,21,21,21,21,18,18,18,18,18,18},
						{18,18,18,18,18,18,18,21,21,21,21,21,21,21,21,21,21,21,18,18,18,18,18,18,18},
						{18,18,18,18,18,18,18,18,21,21,21,21,21,21,21,21,21,18,18,18,18,18,18,18,18},
						{18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18} 
	};

	
	for (int y = 0; y < 19; y++)
	{
		for (int x = 0; x < 25; x++)
		{
			
			if (map[y][x] == 15 || map[y][x] == 16 || map[y][x] ==  33)
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
