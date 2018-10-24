#include "Tile.h"






void Tile::SetBounds(int textureWidth, int textureHeight, int tilesInCol, int tilesInRow)
{
	bounds.left = (int)texturePosition.x * (textureWidth / tilesInCol);
	bounds.top = (int)texturePosition.y*(textureHeight / tilesInRow);
	bounds.right = ((int)texturePosition.x *(textureWidth / tilesInCol)) + (textureWidth / tilesInCol);
	bounds.bottom = ((int)texturePosition.y *(textureHeight / tilesInRow)) + (textureHeight / tilesInRow);
}

Tile::Tile(std::string id, int x, int y, int texPosX, int texPosY, bool collidable)
{
	name = id;
	position.setPos(x, y);
	texturePosition.setPos(texPosX, texPosY);
	isCollidable = collidable;
}


void Tile::Draw(BYTE * textureData, int textureWidth, int textureHeight,  BYTE* screen, int screenwidth, int screenheight, int tilesInCol, int tilesInRow)
{
	SetBounds( textureWidth, textureHeight, tilesInCol, tilesInRow);

	BlitClipping(textureData, screen, screenwidth, screenheight, bounds.left, bounds.top, textureWidth, bounds.Width(),
		bounds.Height(), position.x, position.y);


}

void Tile::BlitClipping(BYTE * textureData, BYTE* screen, int screenWidth, int screenHeight, int  texturePosX, int texturePosY, int textureWidth, int  clippingWidth, int  clippingHeight, float x, float y)const
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
Tile::~Tile()
{
}
