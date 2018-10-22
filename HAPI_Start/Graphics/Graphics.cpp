#include "Graphics.h"


Graphics::Graphics()
{
	
}

//intialises hapi, checks if its ok and returns true as well as setting a screen pointer using the HAPI.getScreenPointer() function
bool Graphics::CreateWindow(const int & Width, const int & Height, string title, unsigned int flag)
{
	screenWidth =  Width;
	screenHeight = Height;
	if (!HAPI.Initialise(screenWidth, screenHeight, title, flag))
	{
		cerr << "Error! Failed to create window. HAPI not initialized..." << endl;

		HAPI.UserMessage("Error! Failed to create window. HAPI not initialized...", "Error");

		return false;
	}
	
	screen = HAPI.GetScreenPointer();
	return true;
}

void Graphics::ClearScreen(unsigned int r, unsigned int g, unsigned int b, unsigned int a)
{
	BYTE * screenPnter = screen;
	HAPI_TColour colour(r, g, b, a);
	for (int i = 0; i < screenWidth*screenHeight*4; i+=4)
	{
		
		*(HAPI_TColour*)screenPnter = colour;
		screenPnter = screen + i;
	}
}

void Graphics::Blit(BYTE * textureData, int & textureWidth, int & textureHeight, float x, float y)const
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

void Graphics::BlitClipping(BYTE * textureData, int  texturePosX, int texturePosY, int textureWidth, int  clippingWidth, int  clippingHeight, float x, float y)const
{
	

	int t_posX =0;
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

	if (x+clippingWidth > screenWidth)
	{
		clippingWidth -= (x + clippingWidth)  - screenWidth;
		
	}
	if (y+clippingHeight > screenHeight)
	{
		clippingHeight -= (y + clippingHeight) - screenHeight;
		
	}

	BYTE * screenPnter = screen + (int)(x + y * screenWidth) * 4;
	BYTE *texturePnter = textureData + ((texturePosX +t_posX)+ (texturePosY +t_posY) * textureWidth) * 4;

	int endOfLineScreenIncrement = (screenWidth - clippingWidth+ t_posX) * 4;
	int endOfTextureIncrement = (textureWidth - clippingWidth+ t_posX) * 4;


	
	for (int row = t_posY; row < clippingHeight ; row++)
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

bool Graphics::Update()
{
	if (HAPI.Update())
	{
		return true;
	}

	cerr << "Closing Window..." << endl;
	return false;
}


void Graphics::CreateSprite(std::string name, int x, int y, int spritesInCol, int spritesInRow)
{
	Sprite *spritePntr = new Sprite(name, x, y, spritesInCol, spritesInRow);
	
	sprites.insert(std::pair<std::string, Sprite*>(name, spritePntr) );
}

void Graphics::CreateTileSet(std::string name,int tilesInCol, int tilesInRow, std::string path)
{
	Tileset *tempTileset = new Tileset(tilesInCol, tilesInRow);

	tempTileset->LoadTexture(path);

	tilesets.insert(std::pair<std::string, Tileset*>(name, tempTileset));

}

bool Graphics::LoadTexture(std::string name, std::string path)const
{
	if (sprites.at(name)->LoadTexture(path))
	{
		return true;
	}


	return false;
}

Graphics::~Graphics()
{
	for (auto sprite : sprites)
		delete sprite.second;
	for (auto t : tilesets)
		delete t.second;
	
	cout << "Detructor" << endl;
}
