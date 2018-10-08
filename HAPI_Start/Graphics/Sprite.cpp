#include "Sprite.h"
#include "Graphics.h"


Sprite::Sprite()
{
	
}

Sprite::Sprite(string name, int x, int y,int spritesInCol, int spritesInRow )
{
	this->spritesInCol = spritesInCol;
	this->spritesInRow = spritesInRow;
	this->name = name;
	position.x = x;
	position.y = y;
	texturePosition.x = 0;
	texturePosition.y = 0;
	
}

void Sprite::Draw(int flag, Graphics *window)
{
	int left = texturePosition.x * (textureWidth / spritesInCol);
	int top = texturePosition.y*(textureHeight / spritesInRow);
	int right = (texturePosition.x *(textureWidth / spritesInCol)) + (textureWidth / spritesInCol);
	int bottom = (texturePosition.y *(textureHeight / spritesInRow)) + (textureHeight / spritesInRow);

	if (flag == 0)
		window->BlitClipping(textureData, left, top, textureWidth, right-left, bottom-top, position.x, position.y);
	else
		window->Blit(textureData, textureWidth, textureHeight, position.x, position.y);
}

bool Sprite::LoadTexture(string path)
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
	
	
}
