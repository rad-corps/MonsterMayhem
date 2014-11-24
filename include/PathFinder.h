#pragma once

#include "Node.h"
#include <vector>
#include <list>
#include <queue>
#include "Vector.h"

using namespace std;

class PathFinder
{
	
public:
	~PathFinder(void);
	PathFinder(void);
	static void SetNodes(vector<vector<Node>> nodes_);
	queue<Node> FindPath(Vector2 start_, Vector2 dest_);
	static Node GetNodeFromPos(Vector2 pos_);
	static float Heuristic(Node current_, Node dest_);
	
private:
	bool IsOnClosedList(Node compare_);	
	static vector<vector<Node>> nodes;
	list<Node> open;
	list<Node> closed;
};

