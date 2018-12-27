#pragma once
#include "..\Add_On\Vector2D.h"
#include <iostream>
#include <vector>


class TileMapEntity;
using namespace std;

struct Node
{
	int parent_i, parant_j;

	double f, g, h;
};

class AI
{
public:
	AI(TileMapEntity map);
	~AI();
private:
	
};

