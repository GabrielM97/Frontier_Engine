#include "Graphics.h"


Graphics::Graphics()
{
	
}

bool Graphics::CreateWindow(const int & Width, const int & Height, string title, unsigned int flag)
{
	screenWidth =  Width;
	screenHeight = Height;
	if (!HAPI.Initialise(screenWidth, screenHeight, title, flag))
	{
		cerr << "Error!\n"
				"Failed to create window."
				"\nHAPI not initialized..." << endl;

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

void Graphics::Blit(BYTE * textureData, int & textureWidth, int & textureHeight, float x, float y)
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
				memcpy(screenPnter, texturePnter,  4);
			
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

			
			
			texturePnter +=  4;
			screenPnter +=  4;
			
		}
		
		
		screenPnter +=  endOfLineScreenIncrement;
		
	}

	
}

void Graphics::BlitClipping(BYTE * textureData, int  texturePosX, int texturePosY, int textureWidth, int  clippingWidth, int  clippingHieght, float x, float y)
{
	

	BYTE * screenPnter = screen + (int)(x + y * screenWidth) * 4;
	BYTE *texturePnter = textureData + (texturePosX + texturePosY * textureWidth) * 4;
	int endOfLineScreenIncrement = (screenWidth - clippingWidth) * 4;
	int endOfTextureIncrement = (textureWidth - clippingWidth) * 4;

	for (int row = 0; row < clippingHieght; row++)
	{

		for (int col = 0; col < clippingWidth; col++)
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



			texturePnter +=  4;
			screenPnter +=  4;

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

bool Graphics::LoadTexture(std::string name, std::string path)
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

	cout << "Detructor" << endl;
}
