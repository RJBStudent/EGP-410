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
	
	gpPerformanceTracker->clearTracker("path");
	gpPerformanceTracker->startTracking("path");
	//allocate nodes to visit list and place starting node in it

	NodeRecord startRecord;
	startRecord.mpNode = pFrom;
	startRecord.mpConnection = NULL;
	startRecord.mCostSoFar = 0;


	//list<Node*> nodesToVisit;
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

	//Node* pCurrentNode = NULL;
	NodeRecord currentNode;
	bool toNodeAdded = false;


	while (/*pCurrentNode != pTo &&*/ nodesToVisit.size() > 0)
	{
		//get current node from front of list
		currentNode = nodesToVisit.front();
				
		if (currentNode.mpNode == pTo)
		{
			break;
		}
		//remove node from list
		nodesToVisit.pop_front();

		//get the Connections for the current node
		vector<Connection*> connections = mpGraph->getConnections(currentNode.mpNode->getId());

		//add all toNodes in the connections to the "toVisit" list, if they are not already in the list
		

		for (unsigned int i = 0; i < connections.size(); i++)
		{
			NodeRecord endNodeRecord = NodeRecord();
			Connection* pConnection = connections[i];
			Node* pEndNode = connections[i]->getToNode();
			int endNodeCost = currentNode.mCostSoFar + connections[i]->getCost();
			bool isVisited = false;
			bool hasntVisited = false;


			for (int i = 0; i < mVisitedNodes.size(); i++)
			{
				if (mVisitedNodes.at(i) == pEndNode)
				{
					isVisited = true;
					break;
				}
			}

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
			else if (hasntVisited)
			{
				pEndNode = iterLocation->mpNode;
				if (endNodeRecord.mCostSoFar <= endNodeCost)
				{
					continue;
				}
			}		
			else
			{
				endNodeRecord = NodeRecord(pEndNode, pConnection, endNodeCost);
			}

			
			if (!hasntVisited && !toNodeAdded)
			{
 				nodesToVisit.push_back(endNodeRecord);
				if (endNodeRecord.mpNode == pTo)
				{
					toNodeAdded = true;
				}
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
		else{
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