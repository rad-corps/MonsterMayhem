#pragma once

#include <vector>
#include "GameObject.h"
#include "Enums.h"

class Terrain :
	public GameObject
{
public:
	Terrain(void);
	virtual ~Terrain(void);

	virtual void Update(float delta_);
	virtual void Draw();

private:
	vector<vector<unsigned int> > tiles;

	unsigned int masterGrassTile;
};

