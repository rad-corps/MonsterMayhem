#include "Terrain.h"
#include "AIE.h"



Terrain::Terrain(void)
{
	masterGrassTile = CreateSprite("./images/Terrain_grass_256.png", TERRAIN_W, TERRAIN_H, true);

	for (int row = 0; row < TERRAIN_ROWS; ++row )
	{
		//vector<unsigned int> rowOfTiles;
		tiles.push_back(vector<unsigned int>());
		for ( int col = 0; col < TERRAIN_COLS; ++col )
		{
			tiles[row].push_back(DuplicateSprite(masterGrassTile));
		}
	}
}


Terrain::~Terrain(void)
{
	cout << "Terrain Destructor Called!!!" << endl;

	for (int row = 0; row < TERRAIN_ROWS; ++row )
	{
		for ( int col = 0; col < TERRAIN_COLS; ++col )
		{
			DestroySprite(tiles[row][col]);
		}
	}
}

void Terrain::Update(float delta_)
{
	for (int row = 0; row < TERRAIN_ROWS; ++row )
	{
		for ( int col = 0; col < TERRAIN_COLS; ++col )
		{
			float xPos = col * (TERRAIN_W);
			float yPos = row * (TERRAIN_H);
			MoveSprite(tiles[row][col], xPos, yPos);
		}
	}
}

void Terrain::Draw()
{
	for (int row = 0; row < TERRAIN_ROWS; ++row )
	{
		for ( int col = 0; col < TERRAIN_COLS; ++col )
		{
			DrawSprite(tiles[row][col]);
		}
	}
}