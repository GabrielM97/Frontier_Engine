#pragma once
#include <HAPI_lib.h>
#include <iostream>
#include <vector>
#include <unordered_map>
#include "Sprite.h"
#include "..\\Add_On\Rectangle.h"


using namespace std;
using namespace HAPISPACE;





class Graphics
{
public:
	Graphics();
	bool CreateWindow(const int & Width, const int & Height, string title, unsigned int flag);
	void ClearScreen(unsigned int r, unsigned int g, unsigned int b, unsigned int a);
	
	bool Update();
	bool CreateSprite(std::string name, int x, int y, int spritesInCol, int spritesInRow, std::string path);

	void Draw(std::string name, RenderType flag, int dir, int state, float posX, float posY);

	void Draw(std::string name, RenderType flag, int dir, int state, float posX, float posY, Vector2D texturePos);
	
	virtual ~Graphics();

	
private:

	Rectangle screenRect;
	int screenWidth;
	int screenHeight;
	BYTE *screen;
	unordered_map<std::string, Sprite*> sprites;




};