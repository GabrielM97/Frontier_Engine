#pragma once
#include <HAPI_lib.h>
#include <iostream>

using namespace std;
using namespace HAPISPACE;
class Graphics
{
public:
	Graphics();
	bool CreateWindow(const int & Width, const int & Height, string title, unsigned int flag);
	void ClearScreen(unsigned int r, unsigned int g, unsigned int b, unsigned int a);
	void Blit(BYTE * textureData, int & textureWidth, int & textureHeight, float x, float y);
	void BlitClipping(BYTE * textureData, int texturePosX, int texturePosY, int textureWidth, int clippingWidth, int clippingHieght, float x, float y);
	bool Update();
	virtual ~Graphics();

	
private:
	int screenWidth;
	int screenHeight;
	BYTE *screen;


};