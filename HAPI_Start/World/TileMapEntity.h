#pragma once
#include "Entity.h"
#include <unordered_map>


struct Tile
{
	std::string name ;
	Vector2D position;
	Vector2D texturePos;
	bool isCollidable;
	Rectangle collisionBox;

	Tile (std::string id, int x, int y, int texPosX, int texPosY, bool collidable)
	{
		name = id;
		position.setPos((float)x, (float)y);
		texturePos.setPos((float)texPosX, (float)texPosY);
		isCollidable = collidable;
	}
};

class TileMapEntity :public Entity
{
public:
	TileMapEntity(std::string tilename, int tilesInCol, int tilesInRow, int w, int h);
	void MakeTile();
	void CreateTileMap();
	void Update();
	void const Render(Graphics* g);
	void CreateCollisionBox(int x, int y, int width, int height);
	void CreateCollisionBox(int x, int y, int width, int height, Tile *t);
	Type GetType() { return entityType; };
	vector<Tile*> getTile() { return tilemap; };
	~TileMapEntity();


private:
	int textureWidth;
	int textureHeight;
	int tilesInCol;
	int tilesInRow;
	
	unordered_map<int, Tile*> tileset;
	vector<Tile*> tilemap;
};

