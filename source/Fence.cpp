#include "Fence.h"
#include "AIE.h"


Fence::Fence(Vector2 startingPos_, TERRAIN_DIRECTION direction_, int numTiles_)
{
	//create the master sprite that all fences will use
	fenceSprite = CreateSprite("./images/Fence.png", 32, 32, true);

	//create all the fence tile positions
	for ( int i = 0; i < numTiles_; ++i )
	{
		Rect tempRect(startingPos_, FENCE_TILE, FENCE_TILE);
		if ( direction_ == TERRAIN_DIRECTION::TERRAIN_DIRECTION_UP) 
			tempRect.SetY(startingPos_.y + FENCE_TILE * i);
		if ( direction_ == TERRAIN_DIRECTION::TERRAIN_DIRECTION_RIGHT) 
			tempRect.SetX(startingPos_.x + FENCE_TILE * i);

		tileRects.push_back(tempRect);
	}
}

Fence::Fence()
{
}

Fence::~Fence(void)
{
}

vector<Rect>
	Fence::GetCollisionRects()
{
	return tileRects;
}

void 
Fence::Update()
{
}

void 
Fence::Draw()
{
	for (int i = 0; i < tileRects.size(); ++i )
	{
		MoveSprite(fenceSprite,tileRects[i].Centre().x, tileRects[i].Centre().y);
		DrawSprite(fenceSprite);
	}
}