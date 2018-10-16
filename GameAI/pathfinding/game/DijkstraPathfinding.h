#pragma once

#include "GridPathfinder.h"
#include <vector>


class Path;
class Graph;
class GraphicsBuffer;
class Grid;
class Connection;//might need to be commented out


class DijkstraPathfinding :public GridPathfinder
{
public:
	DijkstraPathfinding(Graph* pGraph);
	~DijkstraPathfinding();

	Path* findPath(Node* pFrom, Node* pTo);//make sure to delete the path when you are done!

private:
	struct NodeRecord : public Trackable
	{
		NodeRecord() : mpNode(NULL), mpConnection(NULL), mCostSoFar(0) {}
		NodeRecord(Node* node, Connection* connection, int cost) : mpNode(node), mpConnection(connection), mCostSoFar(cost){}
		Node* mpNode;
		Connection* mpConnection;
		int mCostSoFar;
	};
};


