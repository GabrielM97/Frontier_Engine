#include "Graphics.h"


Graphics::Graphics()
{
	
}

//intialises hapi, checks if its ok and returns true as well as setting a screen pointer using the HAPI.getScreenPointer() function
bool Graphics::CreateWindow(const int & Width, const int & Height, string title, unsigned int flag)
{
	screenWidth =  Width;
	screenHeight = Height;
	HAPI.Initialise(screenWidth, screenHeight, title, flag);
	
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



bool Graphics::Update()
{
	if (HAPI.Update())
	{
		return true;
	}

	cerr << "Closing Window..." << endl;
	HAPI.Close();
	return false;
}


bool Graphics::CreateSprite(std::string name, int spritesInCol, int spritesInRow, std::string path)
{

	Sprite *spritePntr  = new Sprite(name, spritesInCol, spritesInRow);

	sprites.insert(std::pair<std::string, Sprite*>(name, spritePntr));

	if (sprites.at(name)->LoadTexture(path))
	{
		
		return true;
	}

	return false;
	
}

void Graphics::Draw(std::string name, RenderType flag, int dir, int state, float posX, float posY)
{
	if(dir != 4 || state != 3)
		sprites.at(name)->Animate(dir, state);
	sprites.at(name)->Draw(flag, screen, screenWidth, screenHeight, posX, posY);
}

void Graphics::Draw(std::string name, RenderType flag, int dir, int state, float posX, float posY, Vector2D texturePos)
{
	if (dir != 4 || state != 3)
		sprites.at(name)->Animate(dir, state);
	sprites.at(name)->Draw(flag, screen, screenWidth, screenHeight, posX, posY, texturePos);
}

Graphics::~Graphics()
{
	for (auto s : sprites)
	{
		delete s.second;
	}
	
	
	cout << "Detructor" << endl;
}
