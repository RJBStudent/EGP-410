#pragma once

#include "GridPathfinder.h"
#include <vector>


class Path;
class Graph;
class GraphicsBuffer;
class Grid;

class AStarPathfinding :public GridPathfinder
{
public:
	AStarPathfinding(Graph* pGraph);
	~AStarPathfinding();

	Path* findPath(Node* pFrom, Node* pTo);//make sure to delete the path when you are done!

private:
};

