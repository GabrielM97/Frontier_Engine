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
	

	return true;
}

void Graphics::ClearScreen(unsigned int r, unsigned int g, unsigned int b, unsigned int a)
{
	HAPI_TColour colour(r, g, b, a);
	for (int i = 0; i < screenWidth*screenHeight*4; i+=4)
	{
		BYTE * pnter = HAPI.GetScreenPointer() + i;
		*(HAPI_TColour*)pnter = colour;
	}
}

void Graphics::Blit(BYTE * textureData, int & textureWidth, int & textureHeight, float x, float y)
{
	unsigned int offset;
	unsigned int tOffset;
	BYTE * pnter;

	for (int sHeight = 0; sHeight < textureHeight; sHeight++)
	{
		for (int sWidth = 0; sWidth < textureWidth; sWidth++)
		{
			offset = (((sWidth + x) + (sHeight + y) * screenWidth) * 4);
			tOffset = (sWidth + sHeight * textureWidth) * 4;
			pnter = HAPI.GetScreenPointer();

			pnter[offset] = textureData[tOffset];
			pnter[offset + 1] = textureData[tOffset + 1];
			pnter[offset + 2] = textureData[tOffset + 2];
			pnter[offset + 3] = textureData[tOffset + 3];



		}
	}
}

void Graphics::BlitClipping(BYTE * textureData, int  texturePosX, int texturePosY, int textureWidth, int  clippingWidth, int  clippingHieght, float x, float y)
{
	unsigned int offset;
	unsigned int tOffset;
	BYTE * pnter;

	for (int sHeight = texturePosY; sHeight < clippingHieght; sHeight++)
	{
		for (int sWidth = texturePosX; sWidth < clippingWidth; sWidth++)
		{
			offset = (((sWidth+ x-clippingWidth) + (sHeight + y - clippingHieght) * screenWidth) * 4);
			tOffset = (sWidth + sHeight * textureWidth) * 4;
			pnter = HAPI.GetScreenPointer();

			pnter[offset] = textureData[tOffset];
			pnter[offset + 1] = textureData[tOffset + 1];
			pnter[offset + 2] = textureData[tOffset + 2];
			pnter[offset + 3] = textureData[tOffset + 3];



		}
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
