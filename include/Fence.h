#pragma once

#include "Vector.h"
#include "Enums.h"
#include <vector>
#include <map>
#include "Rect.h"

class Fence
{
public:
	Fence();
	Fence(Vector2 startingPos_, TERRAIN_DIRECTION direction_, int numTiles_);
	~Fence(void);

	void Update();
	void Draw();

	vector<Rect> GetCollisionRects();

private:
	//map<unsigned int, Rect> tileSprites;

	unsigned int fenceSprite;
	
	//this duplicates the above in memory but will be easier to access when we just want the Rects
	vector<Rect> tileRects; 
	
	

};

