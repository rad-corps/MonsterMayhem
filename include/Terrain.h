//////////////////////////////////////////////////////////////////////////
// Monster Mayhem
// Game Code By Adam Hulbert
// For AIE Advanced Diploma - Practice Production Term 4 2014
//
// Terrain.h
/////////////////////////////////////////////////////////////////////////

#pragma once

#include <vector>
#include <map>
#include "GameObject.h"
#include "Enums.h"
#include "Rect.h"
#include "Node.h"

struct RiverTileInfo
{
	pair<int, int> pos;
	FOUR_WAY_ROTATION direction;
	RIVER_TILE_TYPE type;
};

class Terrain :
	public GameObject
{
public:
	Terrain(void);
	virtual ~Terrain(void);

	virtual void Update(float delta_);
	virtual void Draw();

	void Load(string fileName_);

	void SetRiverTile(int col_, int row_,FOUR_WAY_ROTATION direction_, RIVER_TILE_TYPE type_);
	void SetTreeTile(int col_, int row_);
	
	//used for collision detection
	vector<Rect> GetUnwalkableTerrain();

private:
	void ProcessCSVToTerrain(vector<string> rowText, int rowNum_);

	vector<RiverTileInfo> riverTiles;
	vector<pair<int,int>> treeTiles;
	vector<Rect> unwalkableTerrain;

	unsigned int masterGrassTile;
	unsigned int straightRiver;
	unsigned int cornerRiver;
	unsigned int treeTile;
};

