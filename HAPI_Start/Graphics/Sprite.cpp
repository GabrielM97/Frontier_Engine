#include "Sprite.h"
#include "Graphics.h"
#include "..\Rectangle.h"

Sprite::Sprite()
{
	
}

Sprite::Sprite(string name, int x, int y,int spritesInCol, int spritesInRow )
{
	this->spritesInCol = spritesInCol;
	this->spritesInRow = spritesInRow;
	this->name = name;
	position.x = (float)x;
	position.y = (float)y;
	texturePosition.x = 0;
	texturePosition.y = 0;
	
}

void Sprite::Draw(int flag, Graphics *window)
{
	SetBounds();
	CreateCollisionBox(position.x, position.y, bounds.Width(), bounds.Height());
	if (flag == 0)
		window->BlitClipping(textureData, bounds.left, bounds.top, textureWidth, bounds.Width(), 
			bounds.Height(), position.x, position.y);
	else
		window->Blit(textureData, textureWidth, textureHeight, position.x, position.y);
}

bool Sprite::LoadTexture(string path)
{

	if (!HAPI.LoadTexture(path, &textureData, textureWidth, textureHeight))
	{
		HAPI.UserMessage("Error texture not loaded correctly...", "Error");
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


void Sprite::SetBounds()
{
	bounds.left = (int)texturePosition.x * (textureWidth / spritesInCol);
	bounds.top = (int)texturePosition.y*(textureHeight / spritesInRow);
	bounds.right = ((int)texturePosition.x *(textureWidth / spritesInCol)) + (textureWidth / spritesInCol);
	bounds.bottom = ((int)texturePosition.y *(textureHeight / spritesInRow)) + (textureHeight / spritesInRow);
}

void Sprite::CreateCollisionBox(int x, int y, int width, int height)
{
	collisionBox.left = x;
	collisionBox.top = y;
	collisionBox.right = x + width;
	collisionBox.bottom = y + height;
}

Sprite::~Sprite()
{
	
	
}
