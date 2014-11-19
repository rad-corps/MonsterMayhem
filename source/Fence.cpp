#include "Fence.h"
#include "AIE.h"


Fence::Fence(Vector2 startingPos_, FENCE_DIRECTION direction_, int numTiles_)
{
	for ( int i = 0; i < numTiles_; ++i )
	{
		Rect tempRect(startingPos_, FENCE_TILE, FENCE_TILE);
		if ( direction_ == FENCE_DIRECTION::FENCE_DIRECTION_UP) 
			tempRect.SetY(startingPos.y + FENCE_TILE * i);
		if ( direction_ == FENCE_DIRECTION::FENCE_DIRECTION_RIGHT) 
			tempRect.SetX(startingPos.x + FENCE_TILE * i);

		tileSprites[CreateSprite("./images/Fence.png", 32, 32, true)] = tempRect;

		tileRects.push_back(tempRect);
	}
	direction = direction_;
	startingPos = startingPos_;
}

Fence::Fence()
{
}

Fence::~Fence(void)
{
	for (map<unsigned int,Rect>::iterator it = tileSprites.begin(); it != tileSprites.end(); ++it)
	{
		//DestroySprite(it->first);
	}
}

vector<Rect>
	Fence::GetCollisionRects()
{
	return tileRects;
}

void 
Fence::Update()
{
	for (map<unsigned int,Rect>::iterator it = tileSprites.begin(); it != tileSprites.end(); ++it)
	{
		MoveSprite(it->first, it->second.Centre().x, it->second.Centre().y);
	}
}

void 
Fence::Draw()
{
	for (map<unsigned int,Rect>::iterator it = tileSprites.begin(); it != tileSprites.end(); ++it)
	{
		DrawSprite(it->first);
	}
}