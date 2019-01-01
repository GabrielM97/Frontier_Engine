#include "AI.h"
#include "..\World\TileMapEntity.h"

AI::AI()
{
	
}

void AI::SetStartPosition(Vector2D start)
{
	startPos = start;
}

void AI::SetEndPosition(Vector2D end)
{
	endPos = end;
}


Vector2D AI::FindPath(float speed, int dirNum)
{

	vector<Vector2D> direction;
	direction.resize(dirNum);
	//Directions - left, right, up, down
	
	
	switch (dirNum)
	{

	case 2:
		direction = { Vector2D(-speed, 0), Vector2D(speed,0)};
	case 4:
		direction = { Vector2D(-speed, 0), Vector2D(speed,0), Vector2D(0,-speed),Vector2D(0, speed) };
	
	default:
		break;
	}
	startNode.pos = startPos;

	priorityQueue.clear();

	//Push the start position onto the open list since it's a node that needs to be explored first.
	priorityQueue.push_back(startNode);

	//The algorithm repeats until the start pos aand end position become the same
	if (priorityQueue.at(0).pos == endPos)
	{
		dir = FindDir(priorityQueue.at(0));
		return priorityQueue.at(0).pos;

	}
	else {

		//Popping off the parent
		Node temp = priorityQueue.at(0);
		priorityQueue.pop_back();

		//Generate nighbours of parent
		for (int i = 0; i < direction.size(); i++)
		{
			Node newNode;
			newNode.pos = temp.pos + direction[i];
			newNode.dir = direction[i];

			
			//The x and y differences between the target and the enemy
			Vector2D difference = endPos - newNode.pos;

			//Get the frontier/heuristics of each child of in the priorityQueue
			newNode.hueristic = difference.distance();

			//Check if the new = Node's heuristic against the heuristic of the nodes in the priority queue
			if (i > 0 && newNode.hueristic < priorityQueue.at(0).hueristic)
			{
				priorityQueue.push_back(newNode);

				//Shuffles so that the node with the smallest heuristic is always at the top
				temp = priorityQueue.at(i);
				priorityQueue.at(i) = priorityQueue.at(0);
				priorityQueue.at(0) = temp;
			}
			else
			{
				priorityQueue.push_back(newNode);
			}
		}
	}

	dir = FindDir(priorityQueue.at(0));
	return priorityQueue.at(0).pos;
	
}

AI::~AI()
{
}

int AI::FindDir(const Node & node)
{
	if (node.dir.x != 0)
	{
		if (node.dir.x < 0)
			return 3;
		else if (node.dir.x > 0)
			return 1;
	}
	else if (node.dir.y != 0)
	{
		if (node.dir.y < 0)
			return 2;
		else if (node.dir.y > 0)
			return 0;
	}
	return 3;
}




