#pragma once

#include "Vector.h"
#include <vector>

struct Node
{
	bool walkable;
	Vector2 pos;
	vector<Node*> neighbours;
	Node* parent;
	float g;
	float h;

	bool operator ==(Node compare)
	{
		return pos == compare.pos;
	}

	float F()
	{
		return g + h;
	}

	Node()
	{
		g = 10000000.f;
		h = 10000000.f;
	}


};

