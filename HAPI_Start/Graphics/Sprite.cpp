#include "Sprite.h"



Sprite::Sprite()
{
	renderer = new Graphics();
}

Sprite::Sprite(int x, int y,int spritesInCol, int spritesInRow)
{
	this->spritesInCol = spritesInCol;
	this->spritesInRow = spritesInRow;
	position.x = x;
	position.y = y;
	texturePosition.x = 0;
	texturePosition.y = 0;
	renderer = new Graphics();
}

void Sprite::Draw()
{
	int left = texturePosition.x * (textureWidth / spritesInCol);
	int top = texturePosition.y*(textureHeight / spritesInRow);
	int right = (texturePosition.x *(textureWidth / spritesInCol)) + (textureWidth / spritesInCol);
	int bottom = (texturePosition.y *(textureHeight / spritesInRow)) + (textureHeight / spritesInRow);

	renderer->BlitClipping(textureData,left, top, textureWidth, right, bottom, position.x*(textureWidth / spritesInCol), position.y*(textureHeight / spritesInRow));
}

bool Sprite::LoadSprite(string path)
{

	if (!HAPI.LoadTexture(path, &textureData, textureWidth, textureHeight))
	{
		cerr << "Error texture not loaded correctly..." << endl;
		return false;
	}

	return true;
	
}

void Sprite::Animate(Direction dir, State s)
{
	switch (dir)
	{
	case Direction::SOUTH:
		texturePosition.y = 0;
		break;
	case Direction::NORTH:
		texturePosition.y = 1;
		break;
	case Direction::WEST:
		texturePosition.y = 2;
		break;
	case Direction::EAST:
		texturePosition.y = 3;
		break;

	default:
		cerr << "Something went wrong" << endl;
		break;
	}
	switch (s)
	{
	case State::moving:
		texturePosition.x++;
		break;
	case State::stop:
		texturePosition.x = 0;
		break;
	case State::battle:
		cerr << "Battle" << endl;
		break;
	
	default:
		break;
	}

	if (texturePosition.x > spritesInCol)
	{
		texturePosition.x = 0;
	}
	
}


Sprite::~Sprite()
{
	delete renderer;
	
}
