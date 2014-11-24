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

	void SetRiverTile(int col_, int row_,FOUR_WAY_ROTATION direction_, RIVER_TILE_TYPE type_);
	
	//used for collision detection
	vector<Rect> GetUnwalkableTerrain();
	
	//used for pathfinding
	vector<vector<Node>>& GetNodes();

private:
	vector<RiverTileInfo> riverTiles;
	vector<Rect> unwalkableTerrain;
	vector<vector<Node>> nodes;

	unsigned int masterGrassTile;
	unsigned int straightRiver;
	unsigned int cornerRiver;
};

