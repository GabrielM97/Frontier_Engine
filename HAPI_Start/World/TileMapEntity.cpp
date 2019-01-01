#include "TileMapEntity.h"

#include "..\Graphics\Graphics.h"
#include "..\Add_On\XMLParser.h"
#include "..\Add_On\StringHandler.h"



TileMapEntity::TileMapEntity(std::string tilename, int tInCol, int tInRow, int w, int h)
{

	name = tilename;
	textureWidth = w;
	textureHeight = h;
	tilesInCol = tInCol;
	tilesInRow = tInRow;
	isCollidable = false;
	height = textureHeight / tilesInRow;
	width = textureWidth / tilesInCol;
	entityType = Type::Map;
	isAlive = true;
}

void TileMapEntity::MakeTile()
{
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

void TileMapEntity::CreateTileMap(string file)
{
	GM::XMLParser n(file);

	std::vector<CHapiXMLNode*> layers = n.GetDataFromFile<std::vector<CHapiXMLNode*>>("data");

	mapWidth = n.GetDataFromFile<string>("layer", "width");
	mapHeight = n.GetDataFromFile<string>("layer", "height");

	for (auto& layer : layers)
	{
		auto& map = layer->GetChildren()[0]->GetValue();

		int row = std::stoi(mapWidth);
		int col = std::stoi(mapHeight);
		GM::StringHandler handle;

		vector<string> tiles = handle.SplitString(map.AsString(), col*row, ',');

		for (int i = 0; i < tiles.size(); i++)
		{
			int x = i % row;
			int y = i / row;

			CHapiXMLAttribute attribute;
			layer->GetAttributeWithName("collisionTile", attribute);
			vector<string> collidables = handle.SplitString(attribute.AsString(), attribute.AsString().size(), ',');

			for (auto& c : collidables)
			{
				if (std::stoi(tiles[i]) == std::stoi(c))
				{
					tileset.at(std::stoi(tiles[i]))->isCollidable = true;
				}
			}
			

			tilemap.push_back(new Tile(tileset.at(std::stoi(tiles[i]))->name, x * width, y * height,
				(float)tileset.at(std::stoi(tiles[i]))->texturePos.x, (float)tileset.at(std::stoi(tiles[i]))->texturePos.y,
				tileset.at(std::stoi(tiles[i]))->isCollidable));
		}

	}
	
}

void TileMapEntity::Update()
{
	for each (Tile* t in tilemap)
	{
		CreateCollisionBox(t->position.x, t->position.y, width, height, t);
	}
}

void const TileMapEntity::Render(Graphics * g)
{
	for each ( Tile* t in tilemap)
	{
		g->Draw(name, RenderType::TILE, 4, 3, t->position.x, t->position.y, t->texturePos );
	}
}

void TileMapEntity::CreateCollisionBox(int x, int y, int width, int height)
{
}

void TileMapEntity::CreateCollisionBox(int x, int y, int width, int height, Tile *t)
{
	
	t->collisionBox.left = x;
	t->collisionBox.top = y;
	t->collisionBox.right = x + width;
	t->collisionBox.bottom = y + height;
	
}

TileMapEntity::~TileMapEntity()
{
	for (auto & t : tileset)
		delete t.second;

	for (auto & t : tilemap)
		delete t;

}
