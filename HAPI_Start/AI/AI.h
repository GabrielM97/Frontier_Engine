#pragma once
#include "..\Add_On\Vector2D.h"
#include <iostream>
#include <vector>


class TileMapEntity;
using namespace std;
using namespace GM;

struct Node
{
	float hueristic;
	Vector2D pos;
	Vector2D dir;
};

class AI
{
public:
	AI();
	void SetStartPosition(Vector2D start);
	void SetEndPosition(Vector2D end);

	int getDir() { return dir; };
	
	//gets the speed of the entity to determine where to move to as well as the number of directions the entity can move in.
	Vector2D FindPath(float speed, int dirNum);
	~AI();
private:
	Vector2D startPos, endPos;
	Node startNode;
	int dir = 0;
	std::vector<Node> priorityQueue;
	int FindDir( const Node& node);
	
};

