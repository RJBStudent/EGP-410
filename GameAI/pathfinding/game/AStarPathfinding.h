#pragma once

#include "GridPathfinder.h"
#include <vector>
#include <list>

class Path;
class Graph;
class GraphicsBuffer;
class Grid;
class Connection;

class AStarPathfinding :public GridPathfinder
{
public:
	AStarPathfinding(Graph* pGraph);
	~AStarPathfinding();

	Path* findPath(Node* pFrom, Node* pTo);//make sure to delete the path when you are done!


private:

	struct NodeRecord : public Trackable
	{
		NodeRecord() : mpNode(NULL), mpConnection(NULL), mCostSoFar(0) {}
		NodeRecord(Node* node, Connection* connection, int cost) : mpNode(node), mpConnection(connection), mCostSoFar(cost) {}
		~NodeRecord()
		{
			/*mpNode = NULL;  mpConnection = NULL;*/
		}
		Node* mpNode;
		Connection* mpConnection;
		int mCostSoFar;
		float mEstimateCost;
	};

	float getHeuristic(Node* pFrom, Node* pTo);
	NodeRecord getSmallestElement(std::list<NodeRecord> openList);
};

