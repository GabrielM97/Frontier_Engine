#include "Tile.h"



bool Tile::LoadTexture(string path)
{
	if (!HAPI.LoadTexture(path, &textureData, textureWidth, textureHeight))
	{
		cerr << "Error texture not loaded correctly..." << endl;
		return false;
	}

	return true;
}

void Tile::CreateTileMap()
{
	int map[10][10] = { {0,0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0,0}, 
						{0,0,0,0,0,0,0,0,0,0}, 
						{0,0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0,0},};

	for (int row = 0; row < sizeof(map); row++)
	{
		for (int col = 0; col < sizeof(map[0]); col++)
		{

		}
	}

}

Tile::Tile()
{
}


Tile::~Tile()
{
}
