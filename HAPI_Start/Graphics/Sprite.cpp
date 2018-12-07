
/*
Gabriel Menezes
Milestone 3 < Version 1.3.0 > <05 / 11 / 2018>
----------------------------------------

New Functionality
---------------- -

+Clipping to the screen
+Animation 


Code Additions
--------------
Rectangle Class
	clipToRect(const Rectangle & otherRect)
	Translate(int dx, int dy)
	Intersects(Rectangle & otherRect)
Enum Class direction
Enum class State
Tileset Class
TileClass


Test
----
Able to walk off the screen of all side
Be able to walk back into the screen
The sprite animates correctly
animation only happen when sprite is moving 
Load a high number of sprites both in and out of the screen 1000 sprites

*/

#include "Sprite.h"
#include "..\\Add_On\Rectangle.h"

Sprite::Sprite()
{
	
}

Sprite::Sprite(string name,int spritesInCol, int spritesInRow )
{
	this->spritesInCol = spritesInCol;
	this->spritesInRow = spritesInRow;
	this->name = name;
	texturePosition.x = 0;
	texturePosition.y = 0;
	
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

				//float mod = alpha / 255.0f;
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

	if (x > 0 && x < screenWidth && y > 0 && y > screenHeight)
	{
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

void Sprite::BlitWithoutAlpha(BYTE * screen, int screenWidth, float posX, float posY)
{
	BYTE *screenPnter = screen + (int)(posX + posY * screenWidth)*4;
	BYTE * texturePnter = textureData;

	for (int y = 0; y < textureHeight; y++)
	{
		memcpy(screenPnter, texturePnter, textureWidth * 4);
		
		texturePnter += textureWidth * 4;
		
		screenPnter += screenWidth * 4;
	}
}

void Sprite::Draw(RenderType flag, BYTE* screen, int screenwidth, int screenheight, float posX, float posY)
{
	SetBounds();
	


	switch (flag)
	{

	case RenderType::TILE:
		BlitClipping(textureData, screen, screenwidth, screenheight, bounds.left, bounds.top, textureWidth, bounds.Width(),
			bounds.Height(), posX, posY);
		break;
	case RenderType::TEXTURE:
		Blit(textureData, screen, screenwidth, textureWidth, textureHeight, posX, posY);
		break;

	case RenderType::NO_ALPHA:
		BlitWithoutAlpha(screen, screenwidth, posX, posY);
		break;
	default:
		BlitWithoutAlpha(screen, screenwidth, posX, posY);
		break;
	}
	
}

void Sprite::Draw(RenderType flag, BYTE* screen, int screenwidth, int screenheight, float posX, float posY, Vector2D texturePos)
{
	SetBounds(texturePos);



	switch (flag)
	{

	case RenderType::TILE:
		BlitClipping(textureData, screen, screenwidth, screenheight, bounds.left, bounds.top, textureWidth, bounds.Width(),
			bounds.Height(), posX, posY);
		break;
	case RenderType::TEXTURE:
		Blit(textureData, screen, screenwidth, textureWidth, textureHeight, posX, posY);
		break;

	case RenderType::NO_ALPHA:
		BlitWithoutAlpha(screen, screenwidth, posX, posY);
		break;
	default:
		BlitWithoutAlpha(screen, screenwidth, posX, posY);
		break;
	}

}

bool Sprite::LoadTexture(string path)
{
	
	if (!HAPI.LoadTexture(path, &textureData, textureWidth, textureHeight))
	{
		HAPI.UserMessage("Error texture not loaded correctly...\nPath:" + path, "Error");
		HAPI.Close();
		return false;
	}

	return true;
	
}

void Sprite::Animate(int dir, int s)
{
	if (dir != 4)
	{
		texturePosition.y = dir;
	}

	unsigned int simulationTime{ 50 };
	if(s == 3)
		 simulationTime = 32 ;
	else
		 simulationTime= 16 ;

	DWORD lastTick = 0;
	if (HAPI.GetTime() - lastTick >= simulationTime)
	{

		switch (s)
		{
		case 0:
			texturePosition.x++;

			break;

		case 1:
			texturePosition.x = 0;

			break;

		case 3:
			texturePosition.x++;
			break;

		case 4:
			texturePosition.x++;
		default:
			break;
		}
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


void Sprite::SetBounds(Vector2D texturePos)
{
	bounds.left = (int)texturePos.x * (textureWidth / spritesInCol);
	bounds.top = (int)texturePos.y*(textureHeight / spritesInRow);
	bounds.right = ((int)texturePos.x *(textureWidth / spritesInCol)) + (textureWidth / spritesInCol);
	bounds.bottom = ((int)texturePos.y *(textureHeight / spritesInRow)) + (textureHeight / spritesInRow);
}


Sprite::~Sprite()
{
	delete[] textureData;
	cout << "Sprite Destroy" << endl;
}
