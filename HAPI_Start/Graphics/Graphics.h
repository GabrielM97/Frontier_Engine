#pragma once
#include <iostream>
#include <string>
#include <HAPI_lib.h>


using namespace std;
using namespace HAPISPACE;
class Graphics
{
public:
	Graphics();
	bool CreateWindow(const int &screenWidth, const int &screenHeight, string title, unsigned int flag);
	void ClearScreen(unsigned int r, unsigned  int g, unsigned int b, unsigned int a);
	void Blit(BYTE * textureData, int &textureWidth, int &textureHieght, float x, float y);
	void BlitClipping(BYTE * textureData, int  texturePosX, int texturePosY, int textureWidth, int clippingWidth, int clippingHieght, float x, float y);
	bool Update();
	virtual ~Graphics();
private:
	int screenWidth{ 0 };
	int screenHeight{ 0 };

};

