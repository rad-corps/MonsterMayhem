#include "PathFinder.h"
#include "Enums.h"
#include <list>

vector<vector<Node>> PathFinder::nodes;

PathFinder::PathFinder(void)
{
}


PathFinder::~PathFinder(void)
{
}


void PathFinder::SetNodes(vector<vector<Node>> nodes_)
{
	nodes = nodes_;
}

float PathFinder::Heuristic(Node current_, Node dest_)
{
	return (current_.pos - dest_.pos).GetMagnitude();
}

bool PathFinder::IsOnClosedList(Node compare_)
{
	for (list<Node>::iterator iter = closed.begin(); iter != closed.end(); ++iter )
	{
		if ( compare_ == *iter )
			return true;
	}
	return false;
}

queue<Node>
PathFinder::FindPath(Vector2 start_, Vector2 dest_)
{
	//algorithm
	//1.1 get dest/goal node (node closest to player)
	Node destNode = GetNodeFromPos(dest_);
	
	//1.2 get node closest to begin (push it onto the ret value)
	Node beginNode = GetNodeFromPos(start_);

	Node currentNode;

	//perform a*
	//2.1 create an open and closed list
	open.clear();
	closed.clear();
	list<Node>::iterator toClose;

	//2.2 add the starting square to the open list
	open.push_back(beginNode);

	//2.3 while the target square is not in the closed list
	while (true)
	{

		//2.3.1 find the lowest f score square on the open list and set to current square
		float fScore = 50000000.f; //arbitrary high f score
		for (list<Node>::iterator iter = open.begin(); iter != open.end(); ++iter )
		{
			float heuristic = Heuristic(*iter, destNode);
			float gScore = TERRAIN_W; //TODO multiply by 1.4 for diagonals
			float tempFScore = heuristic + gScore;
			if ( tempFScore < fScore ) 
			{
				fScore = tempFScore;
				currentNode = *iter;
				toClose = iter;
			}

		}
		//2.3.2 switch current node to the closed list and erase from open list
		closed.push_back(currentNode);

		if ( currentNode == destNode )
		{
			break;
		}

		open.erase(toClose);

		//2.3.3  For each of the 8 squares adjacent to this current square
		for (int neighbour = 0; neighbour < currentNode.neighbours.size(); ++neighbour )
		{
			//2.3.3.1 If it is walkable and not on the closed list - 
			if ( currentNode.neighbours[neighbour]->walkable && !IsOnClosedList(*currentNode.neighbours[neighbour]))
			{
				// 2.3.3.1.1 add to the open list
				// 2.3.3.1.2 make current square the parent of this square
				// 2.3.3.1.3 add to the open list
				Node temp;

				//need to check that this makes a copy.
				temp = *currentNode.neighbours[neighbour];
				temp.g = TERRAIN_W;
				temp.h = Heuristic(temp, destNode);
				temp.parent = &currentNode;
				open.push_back(temp);
			}
		}

	};

	queue<Node> ret;

	for (list<Node>::iterator iter = closed.begin(); iter != closed.end(); ++iter )
	{
		ret.push(*iter);
	}

	return ret;
}

Node PathFinder::GetNodeFromPos(Vector2 pos_)
{
	float lowestDist = 5000.0f;//set an arbitrary high distance
	Node ret;

	for (int col = 0; col < TERRAIN_COLS; ++col )
	{
		for (int row = 0; row < TERRAIN_ROWS; ++row )
		{
			float temp_distance = (nodes[row][col].pos - pos_).GetMagnitude();

			if ( temp_distance < lowestDist )
			{
				lowestDist = temp_distance;
				ret = nodes[row][col];
			}
		}
	}
	return ret;
}