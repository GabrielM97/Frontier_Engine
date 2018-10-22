#include "Tileset.h"
#include "Graphics.h"

bool Tileset::LoadTexture(string path)
{
	if (!HAPI.LoadTexture(path, &Data, textureWidth, textureHeight))
	{
		cerr << "Error texture not loaded correctly..." << endl;
		return false;
	}

	return true;
}

void Tileset::CreateTiles()
{
	tileWidth = textureWidth / tilesInCol;
	tileHeight = textureHeight / tilesInRow;
	int id = 0;

	for (int y = 0; y < tilesInRow; y ++)
	{
		for (int x = 0; x < tilesInCol; x++)
		{
			Sprite *tempTile = new Sprite((float)x, (float)y, tilesInCol, tilesInRow);
			tempTile->SetTextureWidthAndHeight(textureWidth, textureHeight);
			tempTile->SetTextureData(Data);
			tempTile->SetName(std::to_string(id));
			tiles.insert(std::pair<int, Sprite*>(id, tempTile));
			id++;
		}

	}

	
}


void Tileset::draw(Graphics * window)
{

	for (auto tile : tilemap)
	{
		
		tile.Draw(0, window);
	}

}

void Tileset::GenerateTilemap()
{
	int map[19][25]={{17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17},
					 {17, 17, 17, 17, 17, 17, 17, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 17, 17, 17, 17, 17, 17, 17},
					 {17, 17, 17, 17, 17, 17, 17, 20, 20, 20, 20, 20, 14, 15, 20, 20, 20, 20, 17, 17, 17, 17, 17, 17, 17},
					 {17, 17, 17, 17, 17, 17, 17, 20, 20, 20, 20, 20, 14, 15, 20, 20, 20, 20, 17, 17, 17, 17, 17, 17, 17},
					 {17, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 14, 15, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 17},
					 {17, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 14, 15, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 17},
					 {17, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 14, 15, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 17},
					 {17, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 14, 15, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 17},
					 {17, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 14, 15, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 17},
					 {17, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 14, 15, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 17},
					 {17, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 14, 15, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 17},
					 {17, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 14, 15, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 17},
					 {17, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 14, 15, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 17},
					 {17, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 14, 15, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 17},
					 {17, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 14, 15, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 17},
					 {17, 17, 17, 17, 17, 17, 17, 20, 20, 20, 20, 20, 14, 15, 20, 20, 20, 20, 17, 17, 17, 17, 17, 17, 17},
					 {17, 17, 17, 17, 17, 17, 17, 20, 20, 20, 20, 20, 14, 15, 20, 20, 20, 20, 17, 17, 17, 17, 17, 17, 17},
					 {17, 17, 17, 17, 17, 17, 17, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 17, 17, 17, 17, 17, 17, 17},
					 {17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17} };










	tilemap.resize(19*25);
	for (int y = 0; y < 19; y++)
	{
		for (int x = 0; x < 25; x++)
		{

			tiles.at(map[y][x])->SetPos(x * tileWidth, y * tileHeight);
			
			
			if (map[y][x] == 14 || map[y][x] == 15)
			{
				tiles.at(map[y][x])->SetIsCollidable(true);
			}
			

			tilemap[(y * 25) + x] = *tiles.at(map[y][x]);

		}
	}



}

Tileset::~Tileset()
{

	for (auto s : tiles)
	{
		delete s.second;
	}


}
