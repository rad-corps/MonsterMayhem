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
#include "FileSettings.h"
#include "FrameworkHelpers.h"

Terrain::Terrain(void)
{
	//initialise sprites
	masterGrassTile = CreateSprite("./images/Terrain_grass_256.png", TERRAIN_W, TERRAIN_H, true);
	straightRiver = CreateSprite("./images/river_straight_256.png", TERRAIN_W, TERRAIN_H, true);
	cornerRiver = CreateSprite("./images/river_corner_256.png", TERRAIN_W, TERRAIN_H, true);
	treeTile = CreateSprite("./images/tree_top_01.png", TERRAIN_W, TERRAIN_H, true);
	mudTile = CreateSprite("./images/mud_128.png", TERRAIN_W, TERRAIN_H, true);
	rockTile = CreateSprite("./images/Rock_01.png", TERRAIN_W, TERRAIN_H, true);
	goalSprite = CreateSprite("./images/goal.png", TERRAIN_W, TERRAIN_H, true);
	timer = 0.0f;
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
			. = Grass							
			
			- = Horozontal river
			
			| = vertical river				
			
		   ___
		   _  \
			| |
		    | |
			\ = angle river					
			
		      ___
			 / __
		    / /
			| |
			/ = rotated angle river			

			| | 
			| |
			\  \__
			 \____
			 6 = rotated angle river

			   | | 
			   | | 
			 __/ /
			 ___ /
			 9 = rotated angle river



		*/

		string bottomTile = rowText[col].substr(0,1);
		string topTile = rowText[col].substr(1,1);

		
		//bottom tiles
		if ( bottomTile == "m" )
		{
			SetMudTile(col, rowNum_);
		}
		else if ( bottomTile == "g" )
		{
			//g by default
		}


		//top tiles
		if ( topTile == "o" )
		{
			SetTreeTile(col, rowNum_);
		}
		else if ( topTile== "|" )
		{
			SetRiverTile(col, rowNum_, FOUR_WAY_ROTATION::ROT_0, RIVER_TILE_TYPE::STRAIGHT);
		}
		else if ( topTile == "-" )
		{
			SetRiverTile(col, rowNum_, FOUR_WAY_ROTATION::ROT_90, RIVER_TILE_TYPE::STRAIGHT);
		}
		else if ( topTile  == "/" )
		{
			SetRiverTile(col, rowNum_, FOUR_WAY_ROTATION::ROT_270, RIVER_TILE_TYPE::CORNER);
		}
		else if ( topTile == "\\" )
		{
			SetRiverTile(col, rowNum_, FOUR_WAY_ROTATION::ROT_180, RIVER_TILE_TYPE::CORNER);
		}
		else if ( topTile == "6" )
		{
			SetRiverTile(col, rowNum_, FOUR_WAY_ROTATION::ROT_0, RIVER_TILE_TYPE::CORNER);
		}
		else if ( topTile == "9" )
		{
			SetRiverTile(col, rowNum_, FOUR_WAY_ROTATION::ROT_90, RIVER_TILE_TYPE::CORNER);
		}
		else if ( topTile == "r" )
		{
			SetRockTile(col, rowNum_);
		}
		else if ( topTile == "g" )
		{
			SetGoalTile(col, rowNum_);
		}
	}
	
	cout << endl;
}

void Terrain::Clear()
{
	riverTiles.clear();
	treeTiles.clear();
	mudTiles.clear();
	rockTiles.clear();
	goalTile = make_pair(0,0);

	unwalkableTerrain.clear();
	mudTerrain.clear();
	unspittableTerrain.clear();
	goalTerrain = Rect();

}

void Terrain::Load(string fileName_)
{
	cout << "Terrain::Load(" << fileName_ << ");" << endl;

	//must clear the existing terrain elements
	Clear();

	ifstream file (fileName_.c_str()); // declare file stream: http://www.cplusplus.com/reference/iostream/ifstream/
	string value;
	//int rowNum = TERRAIN_ROWS - 1;
	int rowNum;

	//get the first line of the file.. 
	//syntax: map_width, map_height, player_x_tile, player_y_tile
	{
		string map_width, map_height, player_x_tile, player_y_tile, slugs, moths, walkers;
		getline ( file, value, '\n' );
		istringstream line_stream(value);	
		getline(line_stream, map_width, ',');
		getline(line_stream, map_height, ',');
		getline(line_stream, player_x_tile, ',');
		getline(line_stream, player_y_tile, ',');
		getline(line_stream, slugs, ',');
		getline(line_stream, moths, ',');
		getline(line_stream, walkers, ',');

		FileSettings::AddIntValue("TERRAIN_COLS", atoi(map_width.c_str()));
		FileSettings::AddIntValue("TERRAIN_ROWS", atoi(map_height.c_str()));
		FileSettings::AddIntValue("PLAYER_X_TILE", atoi(player_x_tile.c_str()));
		FileSettings::AddIntValue("PLAYER_Y_TILE", atoi(player_y_tile.c_str()));
		FileSettings::AddIntValue("BATTLE_FIELD_W", FileSettings::GetInt("TERRAIN_COLS") * TERRAIN_W);
		FileSettings::AddIntValue("BATTLE_FIELD_H", FileSettings::GetInt("TERRAIN_ROWS") * TERRAIN_H);

		FileSettings::AddIntValue("SLUGS", atoi(slugs.c_str()));
		FileSettings::AddIntValue("MOTHS", atoi(moths.c_str()));
		FileSettings::AddIntValue("WALKERS", atoi(walkers.c_str()));
	}

	rowNum = FileSettings::GetInt("TERRAIN_ROWS") - 1;

	while ( file.good() && rowNum >= 0 )
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
    RiverTerrain.push_back(temp);
	//nodes[row_][col_].walkable = false;
}


void Terrain::SetRockTile(int col_, int row_)
{
	rockTiles.push_back(make_pair(col_, row_));
	Rect temp(Vector2(col_ * TERRAIN_W, row_ * TERRAIN_H), TERRAIN_W, TERRAIN_H);
	unwalkableTerrain.push_back(temp);
	unspittableTerrain.push_back(temp);
}

void Terrain::SetMudTile(int col_, int row_)
{
	mudTiles.push_back(make_pair(col_, row_));
	Rect temp(Vector2(col_ * TERRAIN_W, row_ * TERRAIN_H), TERRAIN_W, TERRAIN_H);
	mudTerrain.push_back(temp);
}

void Terrain::SetTreeTile(int col_, int row_)
{
	treeTiles.push_back(make_pair(col_, row_));
	Rect temp(Vector2(col_ * TERRAIN_W, row_ * TERRAIN_H), TERRAIN_W, TERRAIN_H);
	unwalkableTerrain.push_back(temp);
	unspittableTerrain.push_back(temp);
}

void Terrain::SetGoalTile(int col_, int row_)
{
	goalTile = make_pair(col_, row_);
	Rect temp(Vector2(col_ * TERRAIN_W, row_ * TERRAIN_H), TERRAIN_W, TERRAIN_H);
	goalTerrain = temp;
}


void Terrain::Update(float delta_)
{
	timer += delta_;
}

void Terrain::Draw()
{
	//draw the grass tiles
	for (int row = 0; row < FileSettings::GetInt("TERRAIN_ROWS"); ++row )
	{
		for ( int col = 0; col < FileSettings::GetInt("TERRAIN_COLS"); ++col )
		{
			float xPos = col * (TERRAIN_W);
			float yPos = row * (TERRAIN_H);			
			DrawIfOnScreen(masterGrassTile, xPos, yPos);
		}
	}

	//draw the mud tiles
	for (int i = 0; i != mudTiles.size(); ++i )
	{
		//determine position
		float xPos = mudTiles[i].first * (TERRAIN_W);
		float yPos = mudTiles[i].second * (TERRAIN_W);

		DrawIfOnScreen(mudTile, xPos, yPos);
	}

	//draw the rock tiles
	for (int i = 0; i != rockTiles.size(); ++i )
	{
		//determine position
		float xPos = rockTiles[i].first * (TERRAIN_W);
		float yPos = rockTiles[i].second * (TERRAIN_W);

		DrawIfOnScreen(rockTile, xPos, yPos);	
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
		DrawIfOnScreen(tempSprite, xPos, yPos);
		RotateSprite(tempSprite, -rotation);
	}

	//draw the tree tiles
	for (int i = 0; i != treeTiles.size(); ++i )
	{
		//determine position
		float xPos = treeTiles[i].first * (TERRAIN_W);
		float yPos = treeTiles[i].second * (TERRAIN_W);

		DrawIfOnScreen(treeTile, xPos, yPos);
	}

	DrawIfOnScreen(goalSprite, goalTile.first * TERRAIN_W, goalTile.second * TERRAIN_H);
}

vector<Rect> 
Terrain::GetUnwalkableTerrain()
{
	return unwalkableTerrain;
}

vector<Rect> Terrain::GetMudTerrain()
{
	return mudTerrain;
}

vector<Rect> Terrain::GetRiverTerrain()
{
	return RiverTerrain;
}

vector<Rect> Terrain::GetUnspittableTerrain()
{
	return unspittableTerrain;
}

Rect Terrain::GetGoalTile()
{
	return goalTerrain;
}