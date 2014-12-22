//////////////////////////////////////////////////////////////////////////
// Monster Mayhem
// Game Code By Adam Hulbert
// For AIE Advanced Diploma - Practice Production Term 4 2014
// 22/12/2014
// Terrain.cpp
/////////////////////////////////////////////////////////////////////////

#include "Terrain.h"
#include "AIE.h"
#include <fstream>

Terrain::Terrain(void)
{
	//initialise sprites
	masterGrassTile = CreateSprite("./images/Terrain_grass_256.png", TERRAIN_W, TERRAIN_H, true);
	straightRiver = CreateSprite("./images/river_straight_256.png", TERRAIN_W, TERRAIN_H, true);
	cornerRiver = CreateSprite("./images/river_corner_256.png", TERRAIN_W, TERRAIN_H, true);
	treeTile = CreateSprite("./images/tree_top_01.png", TERRAIN_W, TERRAIN_H, true);
}


Terrain::~Terrain(void)
{
	cout << "Terrain Destructor Called!!!" << endl;
	DestroySprite(masterGrassTile);
}

void Terrain::ProcessCSVToTerrain(vector<string> rowText, int rowNum_)
{
	for ( int col = 0; col < rowText.size(); ++col )
	{
		cout << rowText[col];

		/*

			table to convert CSV to Terrain
			. = Grass							DEFAULT
			
			- = Horozontal river
			
			| = vertical river				FOUR_WAY_ROTATION::ROT_0, RIVER_TILE_TYPE::STRAIGHT
			
		   ___
		   _  \
			| |
		    | |
			\ = angle river					FOUR_WAY_ROTATION::ROT_0, RIVER_TILE_TYPE::CORNER
			
		      ___
			 / __
		    / /
			| |
			/ = rotated angle river			FOUR_WAY_ROTATION::ROT_90, RIVER_TILE_TYPE::CORNER

			| | 
			| |
			\  \__
			 \____
			 6 = rotated angle rive

			   | | 
			   | | 
			 __/ /
			 ___ /
			 9 = rotated angle river



		*/

		if ( rowText[col] == "o" )
		{
			SetTreeTile(col, rowNum_);
		}
		else if ( rowText[col] == "|" )
		{
			SetRiverTile(col, rowNum_, FOUR_WAY_ROTATION::ROT_0, RIVER_TILE_TYPE::STRAIGHT);
		}
		else if ( rowText[col] == "-" )
		{
			SetRiverTile(col, rowNum_, FOUR_WAY_ROTATION::ROT_90, RIVER_TILE_TYPE::STRAIGHT);
		}
		else if ( rowText[col] == "/" )
		{
			SetRiverTile(col, rowNum_, FOUR_WAY_ROTATION::ROT_270, RIVER_TILE_TYPE::CORNER);
		}
		else if ( rowText[col] == "\\" )
		{
			SetRiverTile(col, rowNum_, FOUR_WAY_ROTATION::ROT_180, RIVER_TILE_TYPE::CORNER);
		}
		else if ( rowText[col] == "6" )
		{
			SetRiverTile(col, rowNum_, FOUR_WAY_ROTATION::ROT_0, RIVER_TILE_TYPE::CORNER);
		}
		else if ( rowText[col] == "9" )
		{
			SetRiverTile(col, rowNum_, FOUR_WAY_ROTATION::ROT_90, RIVER_TILE_TYPE::CORNER);
		}

	}


	
	cout << endl;
}

void Terrain::Load(string fileName_)
{

	

	ifstream file (fileName_.c_str()); // declare file stream: http://www.cplusplus.com/reference/iostream/ifstream/
	string value;
	int rowNum = TERRAIN_ROWS - 1;

	while ( file.good() )
	{
		string cell;
		getline ( file, value, '\n' );
		istringstream line_stream(value);		
		vector<string> rowCSV;
		while (line_stream.good() )
		{
			getline(line_stream, cell, ',');
			rowCSV.push_back(cell);			
		}
		ProcessCSVToTerrain(rowCSV, rowNum);
		
		--rowNum;
	}
}

void Terrain::SetRiverTile(int col_, int row_,FOUR_WAY_ROTATION direction_, RIVER_TILE_TYPE type_)
{
	//create the river tile info and add to the riverTiles vector
	RiverTileInfo info;
	info.direction = direction_;
	info.pos = make_pair(col_, row_);
	info.type = type_;
	riverTiles.push_back(info);

	//add this tile to the unwalkable terrain
	Rect temp(Vector2(col_ * TERRAIN_W, row_ * TERRAIN_H), TERRAIN_W, TERRAIN_H);
	unwalkableTerrain.push_back(temp);

	//nodes[row_][col_].walkable = false;
}

void Terrain::SetTreeTile(int col_, int row_)
{
	treeTiles.push_back(make_pair(col_, row_));
	Rect temp(Vector2(col_ * TERRAIN_W, row_ * TERRAIN_H), TERRAIN_W, TERRAIN_H);
	unwalkableTerrain.push_back(temp);
}


void Terrain::Update(float delta_)
{

}

void Terrain::Draw()
{
	//draw the grass tiles
	for (int row = 0; row < TERRAIN_ROWS; ++row )
	{
		for ( int col = 0; col < TERRAIN_COLS; ++col )
		{
			float xPos = col * (TERRAIN_W);
			float yPos = row * (TERRAIN_H);
			//DrawSprite(tiles[row][col]);
			MoveSprite(masterGrassTile, xPos, yPos);
			DrawSprite(masterGrassTile);			
		}
	}

	//draw the tree tiles
	for (int i = 0; i != treeTiles.size(); ++i )
	{
		//determine position
		float xPos = treeTiles[i].first * (TERRAIN_W);
		float yPos = treeTiles[i].second * (TERRAIN_W);

		MoveSprite(treeTile, xPos, yPos);			
		//RotateSprite(tempSprite, rotation);
		DrawSprite(treeTile);	
	}

	//draw the river tiles
	for (int i = 0; i != riverTiles.size(); ++i )
	{
		//grab the info
		RiverTileInfo info = riverTiles[i];

		//determine position
		float xPos = info.pos.first * (TERRAIN_W);
		float yPos = info.pos.second * (TERRAIN_W);
		
		//determine rotation
		float rotation;
		switch (info.direction)
		{
		case FOUR_WAY_ROTATION::ROT_0 : 
			rotation = 0.0f;
			break;
		case FOUR_WAY_ROTATION::ROT_90 : 
			rotation = 90.0f;
			break;
		case FOUR_WAY_ROTATION::ROT_180 : 
			rotation = 180.0f;
			break;
		case FOUR_WAY_ROTATION::ROT_270 : 
			rotation = 270.0f;
			break;
		}

		//determine sprite
		unsigned int tempSprite;
		if ( info.type == RIVER_TILE_TYPE::STRAIGHT )
		{
			tempSprite = straightRiver;
		}
		else if ( info.type == RIVER_TILE_TYPE::CORNER )
		{
			tempSprite = cornerRiver;
		}

		//draw the sprite to the screen
		MoveSprite(tempSprite, xPos, yPos);			
		RotateSprite(tempSprite, rotation);
		DrawSprite(tempSprite);	
		RotateSprite(tempSprite, -rotation);
	}
}

vector<Rect> 
Terrain::GetUnwalkableTerrain()
{
	return unwalkableTerrain;
}