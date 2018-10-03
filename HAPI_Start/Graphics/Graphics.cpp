#include "Graphics.h"

int Graphics::screenWidth;
int Graphics::screenHeight;


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
				screenPnter[0] = (BYTE)(mod*blue + (1.0f - mod)*screenPnter[0]);
				screenPnter[1] = (BYTE)(mod*green + (1.0f - mod) * screenPnter[1]);
				screenPnter[2] = (BYTE)(mod*red + (1.0f - mod) * screenPnter[2]);
			}

			
			
			texturePnter +=  4;
			screenPnter +=  4;
			
		}
		
		
		screenPnter +=  endOfLineScreenIncrement;
		
	}

	
}

void Graphics::BlitClipping(BYTE * textureData, int  texturePosX, int texturePosY, int textureWidth, int  clippingWidth, int  clippingHieght, float x, float y)
{
	//unsigned int offset;
	//unsigned int tOffset;
	//

	//for (int sHeight = texturePosY; sHeight < clippingHieght; sHeight++)
	//{
	//	for (int sWidth = texturePosX; sWidth < clippingWidth; sWidth++)
	//	{
	//		offset = (int)(((sWidth+ x-clippingWidth) + (sHeight + y - clippingHieght) * screenWidth) * 4);
	//		tOffset = (sWidth + sHeight * textureWidth) * 4;
	//		screen = HAPI.GetScreenPointer();

	//		screen[offset] = textureData[tOffset];
	//		screen[offset + 1] = textureData[tOffset + 1];
	//		screen[offset + 2] = textureData[tOffset + 2];
	//		screen[offset + 3] = textureData[tOffset + 3];

		

	//	}
	//}

	BYTE * screenPnter = screen + (int)(x + y * screenWidth) * 4;
	BYTE *texturePnter = textureData + (texturePosX + texturePosY * clippingWidth) * 4;
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

				float mod = alpha / 255.0f;
				screenPnter[0] = (BYTE)(mod*blue + (1.0f - mod)*screenPnter[0]);
				screenPnter[1] = (BYTE)(mod*green + (1.0f - mod) * screenPnter[1]);
				screenPnter[2] = (BYTE)(mod*red + (1.0f - mod) * screenPnter[2]);
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


Graphics::~Graphics()
{
}
