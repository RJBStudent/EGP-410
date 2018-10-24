#pragma once

#include "GridPathfinder.h"
#include <vector>
#include <list>


class Path;
class Graph;
class GraphicsBuffer;
class Grid;
class Connection;

//Gridfinder class that calculates the path using Dijkstra. Node Record struct contains a node, connection, and cost.
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
		~NodeRecord()
		{
			/*mpNode = NULL;  mpConnection = NULL;*/
		}
		Node* mpNode;
		Connection* mpConnection;
		float mCostSoFar;
	};

	NodeRecord getSmallestElement(std::list<NodeRecord> openList);
};


