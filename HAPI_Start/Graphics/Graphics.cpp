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



bool Graphics::Update()
{
	if (HAPI.Update())
	{
		return true;
	}

	cerr << "Closing Window..." << endl;
	return false;
}


bool Graphics::CreateSprite(std::string name, int x, int y, int spritesInCol, int spritesInRow, std::string path)
{

	Sprite *spritePntr  = new Sprite(name, x, y, spritesInCol, spritesInRow);

	sprites.insert(std::pair<std::string, Sprite*>(name, spritePntr));

	if (sprites.at(name)->LoadTexture(path))
	{
		
		return true;
	}

	return false;
	
}


bool Graphics::CreateTileset(std::string name, int spritesInCol, int spritesInRow, std::string path)
{

	Tileset * tempTileset = new Tileset( spritesInCol, spritesInRow);

	tilesets.insert(std::pair<std::string, Tileset*>(name, tempTileset));

	if (tilesets.at(name)->LoadTexture(path))
	{

		return true;
	}

	return false;

}

void Graphics::MakeTiles(std::string name)
{
	tilesets.at(name)->MakeTiles();
}

void Graphics::GenerateTileMap(std::string name)
{
	tilesets.at(name)->CreateTileMap();
}

void Graphics::DrawTilemap(std::string name)
{
	tilesets.at(name)->DrawTile(screen, screenWidth, screenHeight);
}


void Graphics::Draw(std::string name, RenderType flag)
{
	sprites.at(name)->Draw(flag, screen, screenWidth, screenHeight);
}

Graphics::~Graphics()
{
	for (auto s : sprites)
	{
		delete s.second;
	}
	for (auto t : tilesets)
	{
		delete t.second;
	}
	cout << "Detructor" << endl;
}
