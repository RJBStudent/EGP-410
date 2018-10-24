#include "DijkstraPathfinding.h"
#include "GridGraph.h"
#include "Node.h"
#include "PerformanceTracker.h"
#include "Game.h"
#include "Path.h"
#include "Connection.h"
#include <list>
#include <vector>
#include <algorithm>

using namespace std;

DijkstraPathfinding::DijkstraPathfinding(Graph* pGraph)
	:GridPathfinder(dynamic_cast<GridGraph*>(pGraph))
{
#ifdef VISUALIZE_PATH
	mpPath = NULL;
#endif

}


DijkstraPathfinding::~DijkstraPathfinding()
{
#ifdef VISUALIZE_PATH
	delete mpPath;
#endif
}

Path* DijkstraPathfinding::findPath(Node* pFrom, Node* pTo)
{
	mpLastFrom = pFrom;
	mpLastTo = pTo;

	if (!mpLastFrom || !mpLastTo)
	{
		return NULL;
	}

	gpPerformanceTracker->clearTracker("path");
	gpPerformanceTracker->startTracking("path");
	//allocate nodes to visit list and place starting node in it

	NodeRecord startRecord;
	startRecord.mpNode = pFrom;
	startRecord.mpConnection = NULL;
	startRecord.mCostSoFar = 0;

	list<NodeRecord> nodesToVisit;
	list<NodeRecord> visitedNodes;

	nodesToVisit.push_front(startRecord);

#ifdef VISUALIZE_PATH
	delete mpPath;
	mVisitedNodes.clear();
	mVisitedNodes.push_back(pFrom);
#endif

	//create Path
	Path* pPath = new Path();

	NodeRecord currentNode;
	bool toNodeAdded = false;


	while (/*pCurrentNode != pTo &&*/ nodesToVisit.size() > 0)
	{
		//get current that is smallest in list
		currentNode = getSmallestElement(nodesToVisit);

		if (currentNode.mpNode == pTo)
		{
			break;
		}
		//remove node from list
		nodesToVisit.pop_front();

		//get the Connections for the current node
		vector<Connection*> connections = mpGraph->getConnections(currentNode.mpNode->getId());


		for (unsigned int i = 0; i < connections.size(); i++)
		{
			NodeRecord endNodeRecord = NodeRecord();
			Connection* pConnection = connections[i];
			Node* pEndNode = connections[i]->getToNode();
			float endNodeCost = currentNode.mCostSoFar + connections[i]->getCost();
			bool isVisited = false;
			bool hasntVisited = false;

			//Check if the current connection is in the closed list
			for (int i = 0; i < mVisitedNodes.size(); i++)
			{
				if (mVisitedNodes.at(i) == pEndNode)
				{
					isVisited = true;
					break;
				}
			}

			//check if the node is in the closed list
			list<NodeRecord>::iterator iterLocation;
			for (list<NodeRecord>::iterator iter = nodesToVisit.begin(); iter != nodesToVisit.end(); ++iter)
			{

				if (iter->mpNode == pEndNode)
				{
					iterLocation = iter;
					hasntVisited = true;
					break;
				}
			}


			if (isVisited) //Figure out how to find visited node record values with the node type
			{
				continue;
			}
			else if (hasntVisited)	//node to the open list location if it hasn't been to it yet, if the cost is less than the current cost ignore it
			{
				pEndNode = iterLocation->mpNode;
				if (endNodeRecord.mCostSoFar <= endNodeCost)
				{
					continue;
				}
			}
			else //if its in neither the closed list or open list add a new node
			{
				endNodeRecord = NodeRecord(pEndNode, pConnection, endNodeCost);
			}

			//if it wasn't in the closed list or open list, add it to the open lost and check if it is the end
			if (!hasntVisited && !toNodeAdded)
			{
				nodesToVisit.push_back(endNodeRecord);
				if (endNodeRecord.mpNode == pTo)
				{
					toNodeAdded = true;
				}
				//Also add it to the closed list
#ifdef VISUALIZE_PATH
				mVisitedNodes.push_back(endNodeRecord.mpNode);
#endif
				visitedNodes.push_back(endNodeRecord);
			}
		}


		for (list<NodeRecord>::iterator iter = nodesToVisit.begin(); iter != nodesToVisit.end(); iter++)
		{
			if (iter->mpNode == currentNode.mpNode)
			{
				nodesToVisit.erase(iter);
				break;
			}
		}
#ifdef VISUALIZE_PATH
		mVisitedNodes.push_back(currentNode.mpNode);
#endif		
		visitedNodes.push_back(currentNode);
	}


	gpPerformanceTracker->stopTracking("path");
	mTimeElapsed = gpPerformanceTracker->getElapsedTime("path");
	if (currentNode.mpNode != pTo)
	{
		return NULL;
	}
	else {
		while (currentNode.mpNode != pFrom)
		{
			pPath->addNode(currentNode.mpNode);
			currentNode.mpNode = currentNode.mpConnection->getFromNode();

			for (list<NodeRecord>::iterator iter = visitedNodes.begin(); iter != visitedNodes.end(); ++iter)
			{
				if (iter->mpNode == currentNode.mpNode)
				{
					currentNode.mpConnection = iter->mpConnection;
					break;
				}
			}
		}
	}

#ifdef VISUALIZE_PATH
	mpPath = pPath;
#endif

	return pPath;

}

//Get the smallest costing node in the list
DijkstraPathfinding::NodeRecord DijkstraPathfinding::getSmallestElement(std::list<NodeRecord> openList)
{
	float lowestCost = INFINITY;
	list<NodeRecord>::iterator iterLocation = openList.begin();
	for (list<NodeRecord>::iterator iter = openList.begin(); iter != openList.end(); ++iter)
	{
		if (iter->mCostSoFar < lowestCost)
		{
			lowestCost = iter->mCostSoFar;
			iterLocation = iter;
		}
	}
	return (*iterLocation);
}