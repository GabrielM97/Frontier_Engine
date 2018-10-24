#include "Sprite.h"
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

void Sprite::SetAttributes(string id, int texPosX, int texPosY, BYTE * data, int tw, int th, int tilesInCol, int tilesInRow)
{

	name = id;
	texturePosition.x = texPosX;
	texturePosition.y = texPosY;
	textureData = data;
	textureWidth = tw;
	textureHeight = th;
	spritesInCol = tilesInCol;
	spritesInRow = tilesInRow;
}

void Sprite::Blit(BYTE * textureData, BYTE* screen, int screenWidth, int & textureWidth, int & textureHeight, float x, float y)const
{

	BYTE * screenPnter = screen + (int)(x + y * screenWidth) * 4;
	BYTE *texturePnter = textureData;
	int endOfLineScreenIncrement = (screenWidth - textureWidth) * 4;


	for (int row = 0; row < textureHeight; row++)
	{

		for (int col = 0; col < textureWidth; col++)
		{
			BYTE alpha = texturePnter[3];

			if (alpha == 255)
			{
				memcpy(screenPnter, texturePnter, 4);

			}
			else if (alpha > 0)
			{
				BYTE blue = texturePnter[0];
				BYTE green = texturePnter[1];
				BYTE red = texturePnter[2];

				float mod = alpha / 255.0f;
				screenPnter[0] = screenPnter[0] + ((alpha*(blue - screenPnter[0])) >> 8);
				screenPnter[1] = screenPnter[1] + ((alpha*(green - screenPnter[1])) >> 8);
				screenPnter[2] = screenPnter[2] + ((alpha*(red - screenPnter[2])) >> 8);
			}



			texturePnter += 4;
			screenPnter += 4;

		}


		screenPnter += endOfLineScreenIncrement;

	}

}

void Sprite::BlitClipping(BYTE * textureData, BYTE* screen, int screenWidth, int screenHeight, int  texturePosX, int texturePosY, int textureWidth, int  clippingWidth, int  clippingHeight, float x, float y)const
{


	int t_posX = 0;
	int t_posY = 0;

	if (x < 0)
	{
		t_posX -= x;
		x = 0;
	}

	if (y < 0)
	{
		t_posY -= y;
		y = 0;
	}

	if (x + clippingWidth > screenWidth)
	{
		clippingWidth -= (x + clippingWidth) - screenWidth;

	}
	if (y + clippingHeight > screenHeight)
	{
		clippingHeight -= (y + clippingHeight) - screenHeight;

	}

	BYTE * screenPnter = screen + (int)(x + y * screenWidth) * 4;
	BYTE *texturePnter = textureData + ((texturePosX + t_posX) + (texturePosY + t_posY) * textureWidth) * 4;

	int endOfLineScreenIncrement = (screenWidth - clippingWidth + t_posX) * 4;
	int endOfTextureIncrement = (textureWidth - clippingWidth + t_posX) * 4;



	for (int row = t_posY; row < clippingHeight; row++)
	{

		for (int col = t_posX; col < clippingWidth; col++)
		{
			BYTE alpha = texturePnter[3];

			if (alpha == 255)
			{
				memcpy(screenPnter, texturePnter, 4);

			}
			else if (alpha > 0)
			{
				BYTE blue = texturePnter[0];
				BYTE green = texturePnter[1];
				BYTE red = texturePnter[2];

				//gives value between 0 and 1;
				float mod = (float)alpha / 255.0f;
				screenPnter[0] = screenPnter[0] + ((alpha*(blue - screenPnter[0])) >> 8);
				screenPnter[1] = screenPnter[1] + ((alpha*(green - screenPnter[1])) >> 8);
				screenPnter[2] = screenPnter[2] + ((alpha*(red - screenPnter[2])) >> 8);
			}



			texturePnter += 4;
			screenPnter += 4;

		}


		screenPnter += endOfLineScreenIncrement;
		texturePnter += endOfTextureIncrement;
	}

}

void Sprite::BlitWithoutAlpha(BYTE * screen, int screenWidth)
{
	BYTE *screenPnter = screen + (int)(position.x + position.y * screenWidth)*4;
	BYTE * texturePnter = textureData;

	for (int y = 0; y < textureHeight; y++)
	{
		memcpy(screenPnter, texturePnter, textureWidth * 4);
		
		texturePnter += textureWidth * 4;
		
		screenPnter += screenWidth * 4;
	}
}

void Sprite::Draw(RenderType flag, BYTE* screen, int screenwidth, int screenheight)
{
	SetBounds();
	CreateCollisionBox(position.x, position.y, bounds.Width(), bounds.Height());


	switch (flag)
	{

	case RenderType::TILE:
		BlitClipping(textureData, screen, screenwidth, screenheight, bounds.left, bounds.top, textureWidth, bounds.Width(),
			bounds.Height(), position.x, position.y);
		break;
	case RenderType::TEXTURE:
		Blit(textureData, screen, screenwidth, textureWidth, textureHeight, position.x, position.y);
		break;

	case RenderType::NO_ALPHA:
		BlitWithoutAlpha(screen, screenwidth);
		break;
	default:
		BlitWithoutAlpha(screen, screenwidth);
		break;
	}
	
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
	delete[] textureData;
	cout << "Sprite Destroy" << endl;
}
